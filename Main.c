//
// Main.c
// Practica4
//
// Created by Beatriz Paulina Garcia Salgado
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "ParallelMatrix.h"

int main(int argc, char** argv)
{
	
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////No cambiar este segmento////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//Variables for matrix operations
	long double* A = NULL;
	long double* B = NULL;
	long double* C = NULL;
	long double count;
	int sizeMat = 100;
	int row,col;
	
	//Variables for thread management and time
	int numThreads;
	struct timespec   t0, t1;
	double tiempoMedido[4];
	
	//Allocate matrices
	A = (long double*)malloc(sizeMat * sizeMat * sizeof(long double));
	B = (long double*)malloc(sizeMat * sizeMat * sizeof(long double));
	C = (long double*)malloc(sizeMat * sizeMat * sizeof(long double));
	if(!A || !B || !C)
	{
		printf("Cannot allocate the matrices\n");
		exit(EXIT_FAILURE);
	}
	
	//Set the maximum number of cores as available threads
	numThreads = getNumberOfCPUs();
	printf("Available cores: %d\n",numThreads);
	omp_set_num_threads(numThreads);
	
	//Initialise the matrices
	for(row = 0; row < sizeMat; row++)
	{
		count = 1;
		for(col = 0; col < sizeMat; col++)
		{
			*(A + row * sizeMat + col) = count;
			*(B + row * sizeMat + col) = 2;
			count++;
		}
	}
	
	checkSumAll(&count, A, sizeMat);
	printf("The addition of all components of A is %Lf\n",count);
	
	checkSumAll(&count, B, sizeMat);
	printf("The addition of all components of B is %Lf\n",count);
	
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	
	//La multiplicacion a realizar es A*B.
	//El maximo debe obtenerse de la matriz A.
	
	//Inserte el codigo solicitado en la practica aqui.
	
	
	if(clock_gettime(CLOCK_REALTIME,&t0) != 0)
	{
		printf("Error al llamar clock_gettime para t0\n");
		exit(EXIT_FAILURE);
	}
	
	matrixMult(&C,A,B,sizeMat);
	checkSumAll(&count, C, sizeMat);
	
	if(clock_gettime(CLOCK_REALTIME, &t1) != 0)
	{
		printf("Error al llamar clock_gettime para t1\n");
		exit(EXIT_FAILURE);
	}
	
	printf("\nLa multiplicacion de los componentes de A y B en C es %Lf\n",count);
	
	tiempoMedido[0] = (double)(t1.tv_sec - t0.tv_sec) + ((double)(t1.tv_nsec - t0.tv_nsec)/1000000000L);
	printf("Tiempo transcurrido: %lf segundos\n",tiempoMedido[0]);
	
	//==============================================================================
	
	if(clock_gettime(CLOCK_REALTIME,&t0) != 0)
	{
		printf("Error al llamar clock_gettime para t0\n");
		exit(EXIT_FAILURE);
	}
	
	ompParallelMatrixMult(&C,A,B,sizeMat);
	checkSumAll(&count, C, sizeMat);
	
	if(clock_gettime(CLOCK_REALTIME, &t1) != 0)
	{
		printf("Error al llamar clock_gettime para t1\n");
		exit(EXIT_FAILURE);
	}
	
	printf("\nLa multiplicacion paralela de los componentes de A y B en C es %Lf\n",count);
	
	tiempoMedido[1] = (double)(t1.tv_sec - t0.tv_sec) + ((double)(t1.tv_nsec - t0.tv_nsec)/1000000000L);
	printf("Tiempo transcurrido: %lf segundos\n",tiempoMedido[1]);
	
	//==============================================================================
	
	if(clock_gettime(CLOCK_REALTIME,&t0) != 0)
	{
		printf("Error al llamar clock_gettime para t0\n");
		exit(EXIT_FAILURE);
	}
	
	matrixMax(&count, C, sizeMat);
	
	if(clock_gettime(CLOCK_REALTIME, &t1) != 0)
	{
		printf("Error al llamar clock_gettime para t1\n");
		exit(EXIT_FAILURE);
	}
	
	printf("\nEl valor maximo de C es %Lf\n",count);
	
	tiempoMedido[2] = (double)(t1.tv_sec - t0.tv_sec) + ((double)(t1.tv_nsec - t0.tv_nsec)/1000000000L);
	printf("Tiempo transcurrido: %lf segundos\n",tiempoMedido[2]);
	
	//==============================================================================
	
	if(clock_gettime(CLOCK_REALTIME,&t0) != 0)
	{
		printf("Error al llamar clock_gettime para t0\n");
		exit(EXIT_FAILURE);
	}
	
	ompParallelMatrixMax(&count, C, sizeMat);
	
	if(clock_gettime(CLOCK_REALTIME, &t1) != 0)
	{
		printf("Error al llamar clock_gettime para t1\n");
		exit(EXIT_FAILURE);
	}
	
	printf("\nEl valor maximo calculado en paralelo de C es %Lf\n",count);
	
	tiempoMedido[3] = (double)(t1.tv_sec - t0.tv_sec) + ((double)(t1.tv_nsec - t0.tv_nsec)/1000000000L);
	printf("Tiempo transcurrido: %lf segundos\n",tiempoMedido[3]);
	
	//==============================================================================
	
	printRegisteredTimes(tiempoMedido);
	
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	
	return EXIT_SUCCESS;
}
