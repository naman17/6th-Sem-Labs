#include <stdio.h>
#include <time.h>
#include <CL/cl.h>
#include <string.h>
#include <stdlib.h>

#define MAX_SOURCE_SIZE (0x100000)

int main(){
	time_t start, end;
	start = clock();

	char tempstr[100];

	for (int i = 0; i < 100; ++i)
		tempstr[i] = 'A';
	
	tempstr[100] = '\0';
	int len = strlen(tempstr);
	len++;

	char *str = (char*)malloc(sizeof(char)*len);
	strcpy(str, tempstr);

	// 1. Load the kernel code

	FILE *kernel_code_file = fopen("strtoggle.cl", "r");
	if (kernel_code_file == NULL) {
		printf("Kernel loading failed.");
		exit(1);
	}

	char *source_str = (char *)malloc(MAX_SOURCE_SIZE);
	size_t source_size = fread(source_str, 1, MAX_SOURCE_SIZE, kernel_code_file);

	fclose(kernel_code_file);

	// 2. Get platform and device information

	cl_platform_id platform_id = NULL;
	cl_device_id device_id = NULL;

	cl_uint ret_num_devices, ret_num_platforms;

	cl_int ret = clGetPlatformIDs(1, &platform_id, &ret_num_platforms);
	ret = clGetDeviceIDs(platform_id, CL_DEVICE_TYPE_CPU, 1, &device_id, &ret_num_devices);


	// 3. Create an OpenCL context
	cl_context context = clCreateContext(NULL, 1, &device_id, NULL, NULL, &ret);


	// 4. Create a command queue

	cl_command_queue command_queue = clCreateCommandQueue(context, device_id, CL_QUEUE_PROFILING_ENABLE, &ret);


	// 5. Create memory buffers on the device for each vector A

	cl_mem mem_obj_s = clCreateBuffer(context, CL_MEM_READ_ONLY, len*sizeof(char), NULL, &ret);
	cl_mem mem_obj_t = clCreateBuffer(context, CL_MEM_READ_ONLY, len*sizeof(char), NULL, &ret);

	// 6. Copy the list A to the respective memory buffers

	ret = clEnqueueWriteBuffer(command_queue, mem_obj_s, CL_TRUE, 0, len * sizeof(char), str, 0, NULL, NULL);

	// 7. Create a program from kernel source

	cl_program program = clCreateProgramWithSource(context, 1, (const char **)&source_str, (const size_t *)&source_size, &ret);
	printf("%d\n", ret);

	// 8. Build the kernel program

	ret = clBuildProgram(program, 1, &device_id, NULL, NULL, NULL);
	printf("%d\n", ret);


	// 9. Create the OpenCL kernel object

	cl_kernel kernel = clCreateKernel(program, "str_chgcase", &ret);


	// 10. Set the arguments of the kernel dode

	ret = clSetKernelArg(kernel, 0, sizeof(cl_mem), (void *)&mem_obj_s);
	ret = clSetKernelArg(kernel, 1, sizeof(cl_mem), (void *)&mem_obj_t);

	// 11. Execute the kernel on device
	
	size_t global_item_size = len;
	size_t local_item_size = 1;

	cl_event event;
	ret = clEnqueueNDRangeKernel(command_queue, kernel, 1, NULL, &global_item_size, &local_item_size, 0, NULL, &event);

	time_t stime = clock();

	cl_ulong time_start, time_end;
	double total_time;

	//Find the kernel execution start time
	clGetEventProfilingInfo(event, CL_PROFILING_COMMAND_START, sizeof(time_start), &time_start, NULL);

	//Find the kernel execution end time
	clGetEventProfilingInfo(event, CL_PROFILING_COMMAND_END, sizeof(time_end), &time_end, NULL);
	total_time = time_end - time_start;



	// 12. Read the memory buffer C on the device to the local variable C, and display

	char *strres = (char*)malloc(sizeof(char)*len);
	ret = clEnqueueReadBuffer(command_queue, mem_obj_t, CL_TRUE, 0, len*sizeof(char), strres, 0, NULL, NULL);

	ret = clFinish(command_queue);
	printf("\nDone\n");
	strres[len-1] = '\0';
	printf("\nResultant toggled string: %s", strres);
	// 13. Clean up

	clFlush(command_queue);
	clReleaseKernel(kernel);
	clReleaseProgram(program);

	clReleaseMemObject(mem_obj_s);
	clReleaseMemObject(mem_obj_t);
	
	clReleaseCommandQueue(command_queue);
	clReleaseContext(context);

	end = clock();
	printf("\n\nTime taken to execute the KERNEL in milliseconds = %0.3f msec\n\n", total_time/1000000);

	printf("\nTime taken to execute the whole program is seconds: %0.3f seconds\n\n", (end - start)*CLOCKS_PER_SEC);
	free(str);
	free(strres);	
	return 0;
}
