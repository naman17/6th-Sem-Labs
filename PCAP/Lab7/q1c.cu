#include<stdio.h>
#include<cuda_runtime.h>
#include<device_launch_parameters.h>
__global__ void add(int *a,int *b,int *c)
{
  int id=blockIdx.x*blockDim.x+threadIdx.x;
  c[id]=a[id]+b[id];
}

int main()
{
  int a[1025],b[1025],c[1025],n;
  printf("Enter n: ");
  scanf("%d",&n);
  printf("Enter A:\n");
  for(int i=0;i<n;i++)
    a[i]=i;
  printf("Enter B:\n");
  for(int i=0;i<n;i++)
    b[i]=i+1;
  int *d_a,*d_b,*d_c;
  int size=sizeof(int)*n;
  cudaMalloc((void**)&d_a,size);
  cudaMalloc((void**)&d_b,size);
  cudaMalloc((void**)&d_c,size);
  cudaMemcpy(d_a,&a,size,cudaMemcpyHostToDevice);
  cudaMemcpy(d_b,&b,size,cudaMemcpyHostToDevice);
  add<<<n,256>>>(d_a,d_b,d_c);
  cudaMemcpy(&c,d_c,size,cudaMemcpyDeviceToHost);
  for(int i=0;i<n;i++)
    printf("%d ",c[i]);
  printf("\n");
  cudaFree(d_a);
  cudaFree(d_b);
  cudaFree(d_c);
}
