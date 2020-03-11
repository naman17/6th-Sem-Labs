#include<stdio.h>
#include<cuda_runtime.h>
#include<device_launch_parameters.h>

__global__ void add(int *A, int *B, int *C, int wa, int wb) {
    // Get the 1D Array index of the matrix
    int row = threadIdx.y;
    int col = threadIdx.x;
    int sum = 0;
    for (int i = 0; i < wa; ++i) {
        sum += (A[row*wa + i] * B[i*wb + col]);
    }
    C[row*wb + col] = sum;
}

int main(){
  int a[100], b[100], c[100], n1, m1, n2, m2;
  printf("Enter m1: ");
  scanf("%d",&m1);
  printf("Enter n1: ");
  scanf("%d",&n1);
  printf("Enter Matrix 1:\n");
  for(int i=0;i<n1*m1;i++)
      scanf("%d",&a[i]);

printf("Enter m2: ");
  scanf("%d",&m2);

  if (m2 != n1){
      printf("cannot be multiplied\n");
      exit(0);
  }

  printf("Enter n2: ");
  scanf("%d",&n2);
  printf("Enter Matrix 2:\n");
  for(int i=0;i<n2*m2;i++)
      scanf("%d",&b[i]);

  int *d_a,*d_b,*d_c;
  cudaMalloc((void**)&d_a,sizeof(int)*n1*m1);
  cudaMalloc((void**)&d_b,sizeof(int)*n2*m2);
  cudaMalloc((void**)&d_c,sizeof(int)*m1*n2);

  cudaMemcpy(d_a,&a,sizeof(int)*n1*m1,cudaMemcpyHostToDevice);
  cudaMemcpy(d_b,&b,sizeof(int)*n2*m2,cudaMemcpyHostToDevice);
  dim3 block(n2, m1, 1);
  add<<<1, block>>>(d_a, d_b, d_c, n1, n2);
  cudaMemcpy(&c,d_c,sizeof(int)*n2*m1,cudaMemcpyDeviceToHost);

  for(int i=0;i<m1*n2;i++){
    if (i % n2 == 0)
      printf("\n");
    printf("%d ",c[i]);
  }
  
  printf("\n");
  cudaFree(d_a);
  cudaFree(d_b);
}
