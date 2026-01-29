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

double u(int number_u, double t, double x);
double u0(int number_u, double x);
double p(double x);
double fun(int number_u, double t, double x);

// implicit scheme - неявная схема
int sweep_method(double *a, double *b, double *c, double *f, double *y, double *alpha, double *beta, int N);
double error(double *previous_nodes, int number_u, int M); // |u*-u|


int toInt(const char *str, int *value);
int toDouble(const char *str, double *value);

void manual (const char *str);

#endif
