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

typedef double (*fun_t)(double, double);

double fun1(double x, double y);
double fun2(double x, double y);
double fun3(double x, double y);
double fun4(double x, double y);
double fun5(double x, double y);

int toInt(const char *str, int *value);
int toDouble(const char *str, double *value);

#endif
