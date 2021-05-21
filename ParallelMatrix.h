//
// ParallelMatrix.h
// Practica4
//
// Created by Beatriz Paulina Garcia Salgado
//

#pragma once

#ifndef ParallelMatrix_h
#define ParallelMatrix_h

#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int getNumberOfCPUs();
int checkSumAll(long double*, long double*, int);
int ompParallelMatrixSum(long double**, long double*, long double*, int);
int matrixSum(long double**, long double*, long double*, int);

////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////Colocar lo que falte aquí////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//Inserte el código para la práctica aqui.
int matrixMult(long double**, long double*, long double*, int);
int ompParallelMatrixMult(long double**, long double*, long double*, int);
int matrixMax(long double*, long double*, int);
int ompParallelMatrixMax(long double* counter, long double* M, int sizeMat);
void printRegisteredTimes(double tiempoMedido[]);

////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif
