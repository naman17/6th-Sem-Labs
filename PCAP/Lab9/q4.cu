#include<stdio.h>
#include<cuda_runtime.h>
#include<device_launch_parameters.h>

__device__ int intToBin(int x){
  return 5;
}

__global__ void add(int *A, int *B, int m, int n) {
    int row = threadIdx.y;
    int col = threadIdx.x;

    if ((row%(m-1) == 0) || (col%(n-1) == 0)){
      B[row*n + col] = A[row*n + col];
    }else{
      B[row*n + col] = intToBin(A[row*n + col]);
    }
}

int main(){
  int a[100], b[100], n, m;
  printf("Enter m: ");
  scanf("%d",&m);
  printf("Enter n: ");
  scanf("%d",&n);
  printf("Enter Matrix:\n");
  for(int i=0;i<n*m;i++)
      scanf("%d",&a[i]);

  int *d_a,*d_b;
  int size = sizeof(int)*m*n;
  cudaMalloc((void**)&d_a,size);
  cudaMalloc((void**)&d_b,size);

  cudaMemcpy(d_a,&a,size,cudaMemcpyHostToDevice);
  cudaMemcpy(d_b,&b,size,cudaMemcpyHostToDevice);

  dim3 block(m, n, 1);
  add<<<1, block>>>(d_a, d_b, m, n);

  cudaMemcpy(&b,d_b,size,cudaMemcpyDeviceToHost);

  for(int i=0;i<n*m;i++){
    if (i % n == 0)
      printf("\n");
    printf("%d ",b[i]);
  }
  
  printf("\n");
  cudaFree(d_a);
  cudaFree(d_b);
}
