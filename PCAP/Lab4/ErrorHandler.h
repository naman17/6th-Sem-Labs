void ErrorHandler(int error_code){

	if (error_code != MPI_SUCCESS){
		char error_string[BUFSIZ];
		int length_of_error_string, error_class;
		MPI_Error_class(error_code, &error_class);
		MPI_Error_string(error_class, error_string, &length_of_error_string);
		fprintf(stderr, " %s %d\n", error_string, length_of_error_string);
		MPI_Error_string(error_code, error_string, &length_of_error_string);
		fprintf(stderr, "HELLO_ERRORCODE %s\n", error_string);
	}
}