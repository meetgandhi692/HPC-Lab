#include<stdio.h>
#include <time.h>
#include <stdlib.h>
const int n = 1024;
const int maskdim = 7;

// CPU function to calculate 2D convolution
void calculate2DConvolutionCPU(int *image, int *mask, int *result, int n, int maskdim) {
    int offset = maskdim / 2;
    for (int row = 0; row < n; row++) {
        for (int col = 0; col < n; col++) {
        result[row * n + col] = 0;
        for (int i = 0; i < maskdim; i++) {
                for (int j = 0; j < maskdim; j++) {
                    int cr = row - offset + i;
                    int cc = col - offset + j;
                    if (cr >= 0 && cr < n && cc >= 0 && cc < n) {
                        result[row * n + col] += image[cr * n + cc] * mask[i * maskdim + j];
                    }
                }
            }
        }
    }
}

__global__ void calculate2DConvolution(int *image, int *mask, int *result, int n, int maskdim) {
    int offset = maskdim / 2;
    int row = blockIdx.y * blockDim.y + threadIdx.y;
    int col = blockIdx.x * blockDim.x + threadIdx.x;
    if (row < n && col < n) {
        int start_row = row - offset;
        int start_col = col - offset;
        for (int i = 0; i < maskdim; i++) {
            for (int j = 0; j < maskdim; j++) {
            if (start_row + i >= 0 && start_row + i < n && start_col + j >= 0 && start_col + j < n) {
                int cr = start_row + i, cc = start_col + j;
                result[row * n + col] += image[cr * n + cc] *
                mask[i * maskdim + j];
                }
            }
        }
    }
}

int main() {
    clock_t start, end;
    start = clock();
    int image[n * n];
    int result[n * n];
    int mask[maskdim * maskdim];
    for (int i = 0; i < n * n; i++) {
        image[i] = rand() % 256; // Randomize the image
    }
    for (int i = 0; i < maskdim * maskdim; i++) {
        mask[i] = rand() % 5; // Randomize the mask
    }
    int *d_image, *d_mask, *d_result;
    
    cudaMalloc(&d_image, n * n * sizeof(int));
    cudaMalloc(&d_mask, maskdim * maskdim * sizeof(int));
    cudaMalloc(&d_result, n * n * sizeof(int));
    cudaMemcpy(d_image, image, n * n * sizeof(int), cudaMemcpyHostToDevice);
    cudaMemcpy(d_mask, mask, maskdim * maskdim * sizeof(int), cudaMemcpyHostToDevice);
    
    int thread = 16;
    int block = (n + thread - 1) / thread;
    
    dim3 blocks(block, block);
    dim3 threads(thread, thread);
    
    // Measure GPU execution time
    cudaEvent_t startGPU, stopGPU;
    cudaEventCreate(&startGPU);
    cudaEventCreate(&stopGPU);
    cudaEventRecord(startGPU);
    calculate2DConvolution<<<blocks, threads>>>(d_image, d_mask, d_result, n, maskdim);
    
    cudaEventRecord(stopGPU);
    cudaEventSynchronize(stopGPU);
    
    float millisecondsGPU = 0;
    cudaEventElapsedTime(&millisecondsGPU, startGPU, stopGPU);
    printf("GPU Execution Time: %f ms\n", millisecondsGPU);
    cudaMemcpy(result, d_result, n * n * sizeof(int), cudaMemcpyDeviceToHost);
    
    // Measure CPU execution time
    start = clock();
    calculate2DConvolutionCPU(image, mask, result, n, maskdim);
    end = clock();
    double durationCPU = ((double)(end - start) * 1000.0) / CLOCKS_PER_SEC;
    
    printf("CPU Execution Time: %f ms\n", durationCPU);
    cudaFree(d_image);
    cudaFree(d_mask);
    cudaFree(d_result);
    return 0;
}