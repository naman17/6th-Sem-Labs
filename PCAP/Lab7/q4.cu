#include<stdio.h>
#include<cuda_runtime.h>
#include<device_launch_parameters.h>
__global__ void add(float *a,float *b){
  
  int id = blockIdx.x*blockDim.x+threadIdx.x;
  b[id] = sinf(a[id]);
}

int main(){
  int n;
  float a[10],b[10];

  printf("Enter n:");
  scanf("%d",&n);

  printf("Enter A:\n");
  for(int i=0;i<n;i++)
    scanf("%f",&a[i]);

  float *d_a,*d_b;
  int size = sizeof(float)*n;

  cudaMalloc((void**)&d_a,size);
  cudaMalloc((void**)&d_b,size);

  cudaMemcpy(d_a,&a,size,cudaMemcpyHostToDevice);
  cudaMemcpy(d_b,&b,size,cudaMemcpyHostToDevice);
  
  add<<<n,1>>>(d_a,d_b);

  cudaMemcpy(&b,d_b,size,cudaMemcpyDeviceToHost);

  for(int i=0;i<n;i++)
    printf("%f ",b[i]);
  printf("\n");
  cudaFree(d_a);
  cudaFree(d_b);
}