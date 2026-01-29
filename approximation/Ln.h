#ifndef _LN_H_    
#define _LN_H_

#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <cstring>
#include <cmath>
#include <cerrno>
#include <climits>

# define PI 3.14159265358979323846
#define EPS 1e-15

double Ln_Phi(double *nodes, int N, double x, int i);

void Ln_create(double *nodes, double *meanings, int N, double *nodes2, double *meanings2);

double Ln_error(double *nodes2, double *meanings1, int N, int number_fun);

#endif
