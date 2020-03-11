#include<stdio.h>
#include<cuda_runtime.h>
#include<device_launch_parameters.h>
__global__ void add(int *a, int *b, int m){

  int id=blockIdx.x*blockDim.x+threadIdx.x;
  // c[id]=a[id]+b[id];
  // printf("id: %d m: %d ", id, m);
  for (int i = 0; i < m; ++i){
    b[id*m + i] = powf(a[id*m + i], id+1);
    // printf("index %d element %d\n", id*m + i, a[id*m + i]);
  }
  
}

int main()
{
  int a[100], b[100],n, m;
  printf("Enter n: ");
  scanf("%d",&n);
  printf("Enter m: ");
  scanf("%d",&m);
  printf("Enter Matrix:\n");
  for(int i=0;i<n*m;i++)
      scanf("%d",&a[i]);

  int *d_a,*d_b;
  int size=sizeof(int)*n*m;
  cudaMalloc((void**)&d_a,size);
  cudaMalloc((void**)&d_b,size);

  cudaMemcpy(d_a,&a,size,cudaMemcpyHostToDevice);
  add<<<n,1>>>(d_a, d_b, m);
  cudaMemcpy(&b,d_b,size,cudaMemcpyDeviceToHost);
  for(int i=0;i<n*m;i++){
    if (i % m == 0)
    {
      printf("\n");
    }
      printf("%d ",b[i]);
  }
      

  printf("\n");
  cudaFree(d_a);
  cudaFree(d_b);
}
