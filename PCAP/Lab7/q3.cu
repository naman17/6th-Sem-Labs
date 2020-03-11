#include<stdio.h>
#include<cuda_runtime.h>
#include<device_launch_parameters.h>
__global__ void add(int *a,int *b, int *al)
{
  int id=blockIdx.x*blockDim.x+threadIdx.x;
  b[id] = (*al)*a[id] + b[id];
}

int main()
{
  int a[10],b[10],n,al;
  printf("Enter n: ");
  scanf("%d",&n);

  printf("Enter alpha: ");
  scanf("%d",&al);

  printf("Enter X:\n");
  for(int i=0;i<n;i++)
    scanf("%d",&a[i]);

  printf("Enter Y:\n");
  for(int i=0;i<n;i++)
    scanf("%d",&b[i]);

  int *d_a,*d_b,*d_c;
  int size = sizeof(int)*n;

  cudaMalloc((void**)&d_a,size);
  cudaMalloc((void**)&d_b,size);
  cudaMalloc((void**)&d_c,sizeof(int));

  cudaMemcpy(d_a,&a,size,cudaMemcpyHostToDevice);
  cudaMemcpy(d_b,&b,size,cudaMemcpyHostToDevice);
  cudaMemcpy(d_c,&al,sizeof(int),cudaMemcpyHostToDevice);
  
  add<<<n,1>>>(d_a,d_b,d_c);

  cudaMemcpy(&b,d_b,size,cudaMemcpyDeviceToHost);

  for(int i=0;i<n;i++)
    printf("%d ",b[i]);
  printf("\n");
  cudaFree(d_a);
  cudaFree(d_b);
  cudaFree(d_c);
}
