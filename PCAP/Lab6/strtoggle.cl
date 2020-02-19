__kernel void str_chgcase(__global char * A, __global char * B){
	int i = get_global_id(0);
	if(A[i] >= 'A' && A[i] <= 'Z')
		B[i] = A[i] + 32;
	else if (A[i] >= 'a' && A[i] <= 'z')
		B[i] = A[i] - 32;
	else
		B[i] = A[i];
}