#include <iostream>
#include <cstdlib>
#include <ctime>

// CUDA kernel for parallel prefix sum
__global__ void prefixSumKernel(int *input, int *output, size_t n) {
    extern __shared__ int temp[];
    int tid = threadIdx.x;
    
    // Load data into shared memory
    temp[tid] = input[tid];
    
    __syncthreads();
    for (int offset = 1; offset < n; offset *= 2) {
        int val = 0;
        if (tid >= offset) {
            val = temp[tid - offset];
        }
        __syncthreads();
        temp[tid] += val;
        __syncthreads();
    }
    output[tid] = temp[tid];
}


int main() {
    const size_t arraySize = 2<<24;  // Adjust the size as needed
    const size_t blockSize = 64; // Adjust the block size as needed

    int *hostInput = new int[arraySize];
    for (size_t i = 0; i < arraySize; ++i) {
        hostInput[i] = rand() % 100; // Adjust the range as needed
    }

    int *deviceInput, *deviceOutput;
    cudaMalloc((void**)&deviceInput, sizeof(int) * arraySize);
    cudaMalloc((void**)&deviceOutput, sizeof(int) * arraySize);

    cudaMemcpy(deviceInput, hostInput, sizeof(int) * arraySize, cudaMemcpyHostToDevice);

    // Define grid size based on block and array size
    size_t gridSize = (arraySize + blockSize - 1) / blockSize;

    prefixSumKernel<<<gridSize, blockSize, blockSize * sizeof(int)>>>(deviceInput, deviceOutput, arraySize);

    int *hostOutput = new int[arraySize];
    cudaMemcpy(hostOutput, deviceOutput, sizeof(int) * arraySize, cudaMemcpyDeviceToHost);


    // Free allocated memory
    delete[] hostInput;
    delete[] hostOutput;
    cudaFree(deviceInput);
    cudaFree(deviceOutput);

    return 0;
}
