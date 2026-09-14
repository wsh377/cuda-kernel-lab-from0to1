#include <cuda_runtime.h>

#include <iostream>

__global__ void environment_check_kernel(int* result)
{
    *result = 42;
}

int main()
{
    int* device_result = nullptr;
    if (cudaMalloc(&device_result, sizeof(int)) != cudaSuccess) {
        std::cerr << "cudaMalloc failed\n";
        return 1;
    }

    environment_check_kernel<<<1, 1>>>(device_result);
    if (cudaDeviceSynchronize() != cudaSuccess) {
        std::cerr << "kernel execution failed\n";
        cudaFree(device_result);
        return 1;
    }

    int host_result = 0;
    if (cudaMemcpy(&host_result, device_result, sizeof(int), cudaMemcpyDeviceToHost) != cudaSuccess) {
        std::cerr << "cudaMemcpy failed\n";
        cudaFree(device_result);
        return 1;
    }

    cudaFree(device_result);
    std::cout << "CUDA kernel result: " << host_result << '\n';
    return host_result == 42 ? 0 : 1;
}
