#ifndef _PM_H_    
#define _PM_H_

#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <cstring>
#include <cmath>
#include <cerrno>
#include <climits>

#define e(i, j, n) ((i-1)*(n) + (j-1))
#define EPS 1e-15

void Pm_create(double *nodes, int N, double *M, double *meanings, double *coef, int *memory); 

void Pm_calculate(double *coef, int N, int m, double *nodes2, double *meanings2);
double Pm_calculate_x(double *coef, int m, double x);

double Pm_error(double *nodes2, double *meanings2, int N, int number_fun);

// Решает СЛУ, представленную матрицей double *M и вектором значений double *b.
//Ответ записывается в double *x. Требует N доп памяти - int *memory
int solve(int n, double *M, double *b, double *x, int *memory);
double fun(int number_fun, double x);

#endif

