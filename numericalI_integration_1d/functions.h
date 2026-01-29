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


#define PI 3.14159265358979323846
#define EPS 1e-15
#define E 2.71828182845904523536

typedef double (*fun_t)(double);

double fun0(double x);
double fun1(double x);
double fun2(double x);
double fun3(double x);
double fun4(double x);
double fun5(double x);
double fun6(double x);
double fun7(double x);
double fun8(double x);
double fun9(double x);

int toInt(const char *str, int *value);
int toDouble(const char *str, double *value);

#endif
