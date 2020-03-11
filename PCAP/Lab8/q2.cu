#include<stdio.h>
#include<cuda_runtime.h>
#include<device_launch_parameters.h>
#include<string.h>

__global__ void reverse( char *ip, int len){
    // Get the index of the current element to be processed
    int i = blockIdx.x*blockDim.x+threadIdx.x;
    int start = 0;
    int end = 0;
  for(int j=0;j<len;++j) {
    if(ip[j] == ' ' || ip[j] == '\0'){
      i--;
      if(i == 0) start = j+1;
      if(i < 0){
        end = j-1;
        break;
      }
    }
  }
  while(start < end){
    i = ip[start];
    ip[start++] = ip[end];
    ip[end--] = i;
  }
}

int main(){
  int n, len;
  char a[100],b[100];

  printf("Enter string:\n");
  gets(a);
  printf("Enter n:\n");
  scanf("%d", &n);

  len = strlen(a);
  a[len++] = ' ';
  a[len] = '\0';

  char *d_a;
  memset(b, 0, 100);

  cudaMalloc((void**)&d_a,len);

  cudaMemcpy(d_a,&a,len,cudaMemcpyHostToDevice);
  
  reverse<<<n,1>>>(d_a, len);

  cudaMemcpy(&b,d_a,len,cudaMemcpyDeviceToHost);

  printf("%s\n", b);
  cudaFree(d_a);
}