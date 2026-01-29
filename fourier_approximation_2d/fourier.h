#ifndef _FOURIER_H_    
#define _FOURIER_H_

#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <cmath>
#include <cerrno>
#include <climits>


#define u(i, j, N) massive_u[(i) * (N)+ (j)]
#define c(i, j, N) massive_c[(i) * (N) + (j)]
#define phi(i, j, N) massive_phi[(i) * (N) + (j)]

# define PI 3.14159265358979323846
#define EPS 1e-15

void print_result(double *massive_c, double *massive_dots, int number_fun, int N);

void fourier_to_c(double *massive_c, double *massive_phi, double *massive_u, double *massive_dots, int number_fun, int N);
double fun(int number_fun, double x, double y);

void make_points(double *massive_dots, int N);
void make_fun(double *massive_u, double *massive_dots, int number_fun, int N);

void create_phi(double *massive_phi, int k, int N);
double scalar_product(double *massive_phi, double *massive_u, int N);
void make_coef_1d(double *massive_c, double *massive_u, double *massive_phi,  int N);


double back_fourier(double *massive_c, double x, double y, int N);
double norma(double *massive_c, int number_fun, int N);

int toInt(const char *str, int *value);

#endif
