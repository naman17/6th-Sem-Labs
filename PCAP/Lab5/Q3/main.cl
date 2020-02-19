__kernel void swapping(__global int *A) {

	int i = get_global_id(0);
	if(i%2 == 1){
		int c = A[i];
		A[i] = A[i-1];
		A[i-1] = c;
	}
}