#include <iostream>
#include <hip/hip_runtime.h>
#include <cassert>
#include <cstddef>


__global__ void calc(const float* a,
                     float* b,
                     unsigned long sz) {

    const unsigned long id = threadIdx.x + blockIdx.x * blockDim.x;

    if(id < sz) {
        for(int i = 0; i < 10000; i++)
            b[id] = 3 * a[id];
    }
    
}

int main() {

    float* a_d;
    float* b_d;
    unsigned long sz = sizeof(float) * 1024 * 1024 * 1024;
    hipMalloc(&a_d, sz);
    hipMalloc(&b_d, sz);
    
    calc<<<dim3(1024 * 1024 * 2), dim3(512), 0, hipStreamDefault>>>(a_d, b_d, sz);

    hipDeviceSynchronize();

    hipFree(a_d);
    hipFree(b_d);

    return 0;
}

