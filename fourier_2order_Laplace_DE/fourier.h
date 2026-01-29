#ifndef _FOURIER_H_    
#define _FOURIER_H_

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

//матрица Фурье размера (N - 1) * (N - 1)
void make_fourier_matrix(double *A, int N, double p);

//void make_fourier_matrix_without_0(double *A, int N, double p);

void make_b_from_A(double *A, int N, double *b);
void make_b_from_x(double p, double *x, int N, double *b);
void make_b_from_f(double *b, int N, int number_fun);

void method_fourier(double *y, int N, double p, double *f);
double psi(int k, int m, int N);
double lambda_m(int m, int N, double p);
double d_m(int m, double *f, int N);


#endif

