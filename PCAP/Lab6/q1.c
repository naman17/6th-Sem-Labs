#include <stdio.h>
#include <time.h>
#include <CL/cl.h>
#include <string.h>
#include <stdlib.h>

#define MAX_DATA_SIZE (1024)

int main (int argc, char** argv) {
	
	int err;                            // error code returned from api calls

	size_t global_work_size;			// global domain size for our calculation
	size_t local_work_size;				// local domain size for our calculation

	cl_platform_id platform_id;			// compute platform id
	cl_device_id device_id;				// compute device id
	cl_context context;					// compute context
	cl_command_queue command_queue;		// compute command queue
	cl_program program;					// compute program
	cl_kernel kernel;					// compute kernel
	
	cl_mem mem_input;					// device memory used for the input array
	cl_mem mem_output;					// device memory used for the output array
	
	int i = 0;
	
	char tempstr[100];
	printf("Enter the string\n");
	scanf("%s", &tempstr);

	int len = strlen(tempstr);
	len++;

	int n;
	printf("Enter n\n");
	scanf("%d", &n);

	char *data = (char*)malloc(sizeof(char)*len);
	strcpy(data, tempstr);

	unsigned int length = strlen(data);

	char *results = (char *)malloc(length * n * sizeof(char));
	
	FILE *kernel_code_file = fopen("q1.cl", "r");
	if (kernel_code_file == NULL) {
		printf("Kernel loading failed.");
		exit(1);
	}
	
	char *source_str = (char *)malloc(MAX_DATA_SIZE);
	size_t source_size = fread(source_str, 1, MAX_DATA_SIZE, kernel_code_file);
	source_str[source_size] = '\0'; // VERY IMPORTANT, cause random C stuff.
	
	fclose(kernel_code_file);
	
	err = clGetPlatformIDs(1, &platform_id, NULL);
	err = clGetDeviceIDs(platform_id, CL_DEVICE_TYPE_CPU, 1, &device_id, NULL);

	context = clCreateContext(0, 1, &device_id, NULL, NULL, &err);

	command_queue = clCreateCommandQueue(context, device_id, 0, &err);

	mem_input = clCreateBuffer(context,  CL_MEM_READ_ONLY,  sizeof(char) * length, NULL, NULL);
	mem_output = clCreateBuffer(context,  CL_MEM_WRITE_ONLY,  sizeof(char) * length * n, NULL, NULL);
	
	err = clEnqueueWriteBuffer(command_queue, mem_input, CL_TRUE, 0, sizeof(char) * length, data, 0, NULL, NULL);
	
	program = clCreateProgramWithSource(context, 1, (const char **)&source_str, NULL, &err);
	
	err = clBuildProgram(program, 0, NULL, NULL, NULL, NULL);
	kernel = clCreateKernel(program, "multiply", &err);

	err  = clSetKernelArg(kernel, 0, sizeof(cl_mem), &mem_input);
	err  = clSetKernelArg(kernel, 1, sizeof(int), &n);
	err  = clSetKernelArg(kernel, 2, sizeof(int), &length);
	err  = clSetKernelArg(kernel, 3, sizeof(cl_mem), &mem_output);
	
	global_work_size = length;
	local_work_size = 1;
	
	err = clEnqueueNDRangeKernel(command_queue, kernel, 1, NULL, &global_work_size, &local_work_size, 0, NULL, NULL);

 	clFinish(command_queue); // Wait for the command commands to get serviced before reading back results
	
	err = clEnqueueReadBuffer(command_queue, mem_output, CL_TRUE, 0, sizeof(char) * length * n, results, 0, NULL, NULL );
	
	printf("%s\n", results);
	clReleaseMemObject(mem_input);
	clReleaseMemObject(mem_output);
	clReleaseProgram(program);
	clReleaseKernel(kernel);
	clReleaseCommandQueue(command_queue);
	clReleaseContext(context);

	return 0;
	
}