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

double fun(int number_fun, double x);

int toInt(const char *str, int *value);
int toDouble(const char *str, double *value);

void manual (const char *str);

#endif
