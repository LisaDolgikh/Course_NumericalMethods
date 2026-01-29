#ifndef _FOURIER_H_    
#define _FOURIER_H_

#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <cmath>
#include <cerrno>
#include <climits>

# define PI 3.14159265358979323846
#define EPS 1e-15

void fourier_to_c(double *massive_c, double *massive_phi, double *massive_u, int Nx, int Ny);

void create_phi(double *massive_phi, int k, int N);
double scalar_product(double *massive_phi, double *massive_u, int N);
void make_coef_1d(double *massive_c, double *massive_u, double *massive_phi,  int N);


double back_fourier(double *massive_c, double x, double y, int Nx, int Ny);
double error(double *matrix_c, int number_u, int Nx, int Ny, double T);
double error_plus(double *matrix_c, int number_u, int Nx, int Ny, double T, int *i_max, int *j_max);
double error_2(double *matrix_u, int number_u, int Nx, int Ny, double T);

#endif
