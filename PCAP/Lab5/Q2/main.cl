__kernel void ones_comp(__global int *A, __global int *B) {
	int i = get_global_id(0);
	 int bin = A[i];
	 int ones = 0;
	 int b;
	 int p = 1;
	while (bin > 0) {
		b = bin % 10;
		if (b == 0){
			ones = 1*p + ones;
		}else{
			ones = ones + 0*p;
		}
		bin /= 10;
		p *= 10;
	}
	B[i] = ones;

}