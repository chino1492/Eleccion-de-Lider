#include <stdio.h>
#include <mpi.h>
#include <string.h>
#include <stdlib.h> 
#include <time.h> 

void mayor(int cadena[],int n,int *pos,int *num);

int main(int argc, char* argv[])
{
        
	int FLAG=123;

	int numeroProcesos, myid, i, j, numero, mapos, manum;
        numeroProcesos=8;

	int numeros[numeroProcesos];
  	MPI_Status stat;
	MPI_Init(&argc, &argv); 
  	MPI_Comm_size(MPI_COMM_WORLD,&numeroProcesos); 
  	MPI_Comm_rank(MPI_COMM_WORLD,&myid);	
        //numero randomico 	
	srand(time(0)+myid);  
	numero=rand()% 37;
	numeros[myid]=numero;
	
	for(i=0;i<numeroProcesos;i++)
   	{		
		if(myid!=i)
		{
			MPI_Send(&numero, 1, MPI_INT, i, FLAG, MPI_COMM_WORLD);
		}			
	}
	
	for(j=0;j<numeroProcesos;j++)
	{	
		if(myid!=j)
		{		
			MPI_Recv(&numero, 1, MPI_INT, j, FLAG, MPI_COMM_WORLD, &stat);
			numeros[j]=numero;
		}
	}
	if((j==numeroProcesos)&&(i==numeroProcesos))
	{
mayor(numeros,numeroProcesos,&mapos,&manum);
		
		if(myid==mapos)
		{FF
printf("Soy el P %d y mi numero es: %d, Yo soy el lider\n",myid,numeros[myid]);
		}
		else
		{
printf("Soy el P %d y mi numero es: %d, Yo no soy el lider\n",myid,numeros[myid]);
		}
	}
  	MPI_Finalize(); 
  	return 0;
}

void mayor(int cadena[],int n,int *pos,int *num){
int i,j;
*pos=0;
*num=cadena[0];

//comparar un vector de numeros
	for (i=0;i<n-1;i++)//numero1 a comparar
    	{
        	for (j=i+1;j<n;j++)//numero2 a comparar
        	{
            		if (*num<cadena[j]){
				*pos=j;
				*num=cadena[j];
				i=j-1;
				j=n;	
			}
        	}
	}
}
