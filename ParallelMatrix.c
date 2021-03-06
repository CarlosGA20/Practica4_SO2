//
// ParallelMatrix.c
// Practica4
//
// Created by Beatriz Paulina Garcia Salgado
//

////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////No cambiar este segmento////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "ParallelMatrix.h"

int getNumberOfCPUs()
/*Gets the number of available cores at the momment
Input: void
Output: number of available cores*/
{
	int numThreads;
	numThreads = omp_get_max_threads();
	return numThreads;
}

int checkSumAll(long double* counter, long double* M, int sizeMat)
/*Performs the addition of all the elements of a square matrix to check operations
Input:	pointer to save the result
	pointer to the matrix
	size of the square matrix
Output: EXIT_FAILURE; EXIT_SUCCESS*/
{
	int element, totalElem;
	if(!counter || !M)
	{
		printf("Error in input pointers\n");
		return EXIT_FAILURE;
	}
	
	totalElem = sizeMat * sizeMat;
	*counter = 0;
	for(element = 0; element < totalElem; element++)
	{
		*counter = *counter + *(M + element);
	}
	
	return EXIT_SUCCESS;
}
	

int ompParallelMatrixSum(long double** result, long double* A, long double* B, int sizeMat)
/*Computes the addition of two square matrices: result = A + B
Input:	pointer to save the result
	pointer to matrix A
	pointer to matrix B
	size of the square matrices
Output: EXIT_FAILURE; EXIT_SUCCESS*/
{
	int element, totalElem;
	
	if(!*result || !A || !B)
	{
		printf("Error in a matrix pointer\n");
		return EXIT_FAILURE;
	}
	
	totalElem = sizeMat * sizeMat;
	
	#pragma omp parallel for
	for(element = 0; element < totalElem; element++)
	{
		*(*result + element) = *(A + element) + *(B + element);
	}
	
	return EXIT_SUCCESS;
}

int matrixSum(long double** result, long double* A, long double* B, int sizeMat)
/*Computes the addition of two square matrices: result = A + B
Input:	pointer to save the result
	pointer to matrix A
	pointer to matrix B
	size of the square matrices
Output: EXIT_FAILURE; EXIT_SUCCESS*/
{
	int element, totalElem;
	
	if(!*result || !A || !B)
	{
		printf("Error in a matrix pointer\n");
		return EXIT_FAILURE;
	}
	
	totalElem = sizeMat * sizeMat;
	
	for(element = 0; element < totalElem; element++)
	{
		*(*result + element) = *(A + element) + *(B + element);
	}
	
	return EXIT_SUCCESS;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//Inserte el c??digo solicitado en la pr??ctica aqui.

int matrixMult(long double** result, long double* A, long double* B, int sizeMat)
{
    	int i,j,k;
    
    	if(!*result || !A || !B)
    	{
       	printf("Error in a matrix pointer\n");
        	return EXIT_FAILURE;
    	}
        
	for (i=0; i<sizeMat; i++)
        {
              for (j=0; j<sizeMat; j++)
              {
                 *(*result + j + (i*sizeMat)) = 0;
                 for (k=0; k<sizeMat; k++)
                 {
                        *(*result + j + (i*sizeMat)) = *(*result + j + (i*sizeMat)) + *(A + k + (j*sizeMat)) * *(B + j + (k*sizeMat));
                 }
              }
       }
       
       return EXIT_SUCCESS;
}

int matrixMax(long double* counter, long double* M, int sizeMat)
{
    int element, totalElem;

    if(!M || !counter)
    {
        printf("Error in input pointers\n");
        return EXIT_FAILURE;
    }

    totalElem = sizeMat * sizeMat;
    *counter = 0;
    for(element = 0; element < totalElem; element++)
    {
        if(*counter < *(M + element))
        {
            *counter = *(M + element);
        }
    }
    
    return EXIT_SUCCESS;
}

int ompParallelMatrixMult(long double** result, long double* A, long double* B, int sizeMat)
{
    	int i,j,k;
    
    	if(!*result || !A || !B)
    	{
        	printf("Error in a matrix pointer\n");
        	return EXIT_FAILURE;
    	}
        
        #pragma omp parallel shared(result,A,B) private(i,j,k) 
   	{
        	#pragma omp for  schedule(static)
        	for (i=0; i<sizeMat; i++)
        	{
              		for (j=0; j<sizeMat; j++)
              		{
                 		*(*result + j + (i*sizeMat)) = 0;
                 		for (k=0; k<sizeMat; k++)
                 		{
                        		*(*result + j + (i*sizeMat)) = *(*result + j + (i*sizeMat)) + *(A + k + (j*sizeMat)) * *(B + j + (k*sizeMat));
                 		}
              		}
       	}
       }
       
       return EXIT_SUCCESS;
}

int ompParallelMatrixMax(long double* counter, long double* M, int sizeMat)
{
    int element, totalElem;

    if(!M || !counter)
    {
        printf("Error in input pointers\n");
        return EXIT_FAILURE;
    }

    totalElem = sizeMat * sizeMat;
    *counter = 0;
    
   #pragma omp parallel shared(counter,M) private(element) 
   {
   	#pragma omp for  schedule(static)
   	for(element = 0; element < totalElem; element++)
   	{
        	if(*counter < *(M + element))
        	{	
            	*counter = *(M + element);
        	}
    	}
    }
    
    return EXIT_SUCCESS;
}

void printRegisteredTimes(double tiempoMedido[])
{
	printf("\n===============================================\n");
	printf("=        Operacion        =       Tiempo      =\n");
	printf("===============================================\n");
	printf("= Multiplicacion          = %lf segundos =\n", tiempoMedido[0]);
	printf("= Multiplicacion paralela = %lf segundos =\n", tiempoMedido[1]);
	printf("= Maximo                  = %lf segundos =\n", tiempoMedido[2]);
	printf("= Maximo paralelo         = %lf segundos =\n", tiempoMedido[3]);
	printf("===============================================\n");
}

