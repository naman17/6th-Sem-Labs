#include<mpi.h>
#include<stdio.h>
#include<string.h>
#define MAX 200

int main(int argc, char *argv[])
{
	int rank,size;
	MPI_Init(&argc,&argv);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Comm_size(MPI_COMM_WORLD,&size);

	int val;
	int total;
	char str[MAX], str2[MAX];
	MPI_Status status;
	if(rank==0)
	{
		FILE *fd = fopen("test.txt","r");
		int cnt = 1;
		while(fgets(str,MAX,fd)!=NULL)
		{
			char *ch1,*ch2;
			if((ch1=strstr(str,"<TEXT>"))&&(ch2=strstr(str,"</TEXT>")))
			{
				ch1+=6;

				int k=0;
				char temp[MAX];
				while(ch1!=ch2)
				{
					temp[k++]=ch1[0];
					ch1++;
				}
				temp[k]='\0';
				strcpy(str2,temp);
				MPI_Send(&str2,(strlen(str)+1),MPI_CHAR,cnt++,1,MPI_COMM_WORLD);
				MPI_Recv(&k,1,MPI_INT,cnt-1,1,MPI_COMM_WORLD,&status);
				printf("Words Recieved from Process %d : %d\n",cnt-1, k);
				total += k;
			}
		}
		printf("Total sum of words: %d\n", total);
		fclose(fd);
	}
	else
	{
		MPI_Recv(&str,MAX,MPI_CHAR,0,1,MPI_COMM_WORLD,&status);
		printf("Line Received by Process %d is %s\n", rank, str);
		int k = 0, words = 1;
		while(str[k] != '\0'){
			if (str[k++] == ' ')
			{
				words++;
			}
		}
		MPI_Send(&words,1,MPI_INT,0,1,MPI_COMM_WORLD);
	}
	MPI_Finalize();
	return 0;
}