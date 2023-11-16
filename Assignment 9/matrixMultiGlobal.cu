#include <stdio.h>
#include <time.h>
const int n = 2<<8;

__global__ void multiply(int *mat1, int *mat2, int *result, int n) {
    int row = blockIdx.y * blockDim.y + threadIdx.y;
    int col = blockIdx.x * blockDim.x + threadIdx.x;
        if (row < n && col < n) {
            for (int k = 0; k < n; k++) {
                result[row * n + col] += mat1[row * n + k] * mat2[k * n + col];
        }
    }
}


int main() {
    int mat1[n * n];
    int mat2[n * n];
    for (int i = 0; i < n * n; i++) {
        mat1[i] = i + 1;
        mat2[i] = n * n - i;
    }
    int result[n * n];
    int *d_mat1, *d_mat2, *d_result;
    cudaMalloc(&d_mat1, n * n * sizeof(int));
    cudaMalloc(&d_mat2, n * n * sizeof(int));
    cudaMalloc(&d_result, n * n * sizeof(int));
    cudaMemcpy(d_mat1, mat1, n * n * sizeof(int),
    cudaMemcpyHostToDevice);
    cudaMemcpy(d_mat2, mat2, n * n * sizeof(int),
    cudaMemcpyHostToDevice);

    size_t blocks=1;
    size_t threads=64;
    
    multiply<<<blocks, threads>>>(d_mat1, d_mat2, d_result, n);
    cudaDeviceSynchronize();
    cudaMemcpy(result, d_result, n * n * sizeof(int),
    cudaMemcpyDeviceToHost);
    
    return 0;
}