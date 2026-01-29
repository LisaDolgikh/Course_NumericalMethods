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

int make_points(int N, double *massive_dots);
void phi(double *massive_phi, int k, int N);
double scalar_product(double *massive_phi, double *massive_u, int N);
int make_coef(double *massive_ck, double *massive_u, double *massive_phi,  int N);
double back_fourier(double *massive_ck, double x, int N);

double u(int number_fun, double x);

double search_norma(double *massive_ck, int number_fun, int N);
double error_fourier(double *massive_ck, double *massive_dots, double *massive_u, double *massive_phi, int number_fun, int N );

int toInt(const char *str, int *value);
void manual (const char *str);

#endif

