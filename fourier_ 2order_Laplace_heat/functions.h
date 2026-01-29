#ifndef _FUNCTIONS_H_    
#define _FUNCTIONS_H_

#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <cstring>
#include <cmath>
#include <cerrno>
#include <climits>
#include <iomanip>


#define PI 3.14159265358979323846
#define EPS 1e-15
#define E 2.71828182845904523536

double u(int number_u, double t, double x, double y);
double u0(int number_u, double x, double y);
double p(double x, double y);
double fun(int number_u, double t, double x, double y);


void make_d_from_f(double *matrix_d, double *massive_phi, double *massive_u, int Nx, int Ny, int number_u, double time);
double lambda_m(int m, int N);
void make_c_from_d_and_previous(double *matrix_d, double *matrix_c, double *previous_nodes, int Nx, int Ny, double tau);

int toInt(const char *str, int *value);
int toDouble(const char *str, double *value);

#endif
