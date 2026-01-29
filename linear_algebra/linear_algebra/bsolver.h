#ifndef _BSOLVER_H_    
#define _BSOLVER_H_

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <cmath>
#include <cerrno>
#include <climits>
//#include <iomanip>
//#include <fstream>
//#include <sstream>
//#include <string>

# define PI 3.14159265358979323846
#define EPS 1e-15

double method_BSolver(double *x, double *A, double *B, double *b, double tau, int N, int mIter, double *mem, double *mem1);
double find_q0(double *A, int N);

void make_matrix_3(double *A, int N, double p);
void reverse_fourier_matrix_without_0(double p, double * B, int N, double * mem1, double * mem2);


#endif