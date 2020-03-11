#include<stdio.h>
#include<cuda_runtime.h>
#include<device_launch_parameters.h>

__global__ void add(int *a, int *b, int *c, int m){

  int id=blockIdx.x*blockDim.x+threadIdx.x;
  c[id] =  a[id] + b[id];
  
}

int main()
{
  int a[100], b[100], c[100],n, m;
  printf("Enter m: ");
  scanf("%d",&m);
  printf("Enter n: ");
  scanf("%d",&n);
  printf("Enter Matrix 1:\n");
  for(int i=0;i<n*m;i++)
      scanf("%d",&a[i]);

  printf("Enter Matrix 2:\n");
  for(int i=0;i<n*m;i++)
      scanf("%d",&b[i]);

  int *d_a,*d_b,*d_c;
  int size=sizeof(int)*n*m;
  cudaMalloc((void**)&d_a,size);
  cudaMalloc((void**)&d_b,size);
  cudaMalloc((void**)&d_c,size);

  cudaMemcpy(d_a,&a,size,cudaMemcpyHostToDevice);
  cudaMemcpy(d_b,&b,size,cudaMemcpyHostToDevice);
  add<<<m, n>>>(d_a, d_b, d_c, m);
  cudaMemcpy(&c,d_c,size,cudaMemcpyDeviceToHost);

  for(int i=0;i<n*m;i++){
    if (i % m == 0)
      printf("\n");
    printf("%d ",c[i]);
  }
  
  printf("\n");
  cudaFree(d_a);
  cudaFree(d_b);
}
