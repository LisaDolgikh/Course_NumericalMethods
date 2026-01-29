#ifndef _MATRIX_H_    
#define _MATRIX_H_

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <cmath>
#include <cerrno>
#include <climits>

void print_matrix(double *matrix, int size, int maxPrintSize);
void print_matrix_1(double * A, int N);
void mult_matrix_vector(double *A, double *x, double *ans, int N);
void print_system(double *matrix, double *rhs, int size, int maxPrintSize);
void print_vector(double *vector, int size, int maxPrintSize);

double residual(double *matrix, double *rhs, double *result, int size); // |Ax*-B|
double error_x(double *result, int size); //|x'-x|
double error(double *matrix, double *rhs, double *result, int size);


#endif