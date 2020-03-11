MPI_Buffer_attach(buffer, size);
MPI_Buffer_detach(&buffer, &size);


MPI_Send(array, 5, MPI_INT, 3, 1, MPI_COMM_WORLD);
MPI_Recv(array2, 5, MPI_INT, 0, 1, MPI_COMM_WORLD);

MPI_Ssend(array, 5, MPI_INT, 3, 1, MPI_COMM_WORLD);
MPI_Recv(array2, 5, MPI_INT, 0, 1, MPI_COMM_WORLD);

MPI_Bsend(array, 5, MPI_INT, 3, 1, MPI_COMM_WORLD);
MPI_Recv(array2, 5, MPI_INT, 0, 1, MPI_COMM_WORLD);


MPI_Scatter(array, 2, MPI_INT, array3, 2, MPI_INT, 0, MPI_COMM_WORLD);
MPI_Gather(array3, 2, MPI_INT, array, 2, MPI_INT, 0 , MPI_COMM_WORLD);