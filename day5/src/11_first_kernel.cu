#include <cstdio>
#include <cuda_runtime.h>

__global__ void hello_from_gpu()
{
    printf("Hello from GPU!\n");
}

int main()
{
    printf("Hello from CPU!\n");

    hello_from_gpu<<<1, 1>>>();

    cudaDeviceSynchronize();

    return 0;
}