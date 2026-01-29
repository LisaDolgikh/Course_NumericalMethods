#ifndef _INTERPOLATION_H_    
#define _INTERPOLATION_H_

#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <cstring>
#include <cmath>
#include <cerrno>
#include <climits>

#include "Pm.h"

#define PI 3.14159265358979323846
#define EPS 1e-15
#define E 2.71828182845904523536

double fun(int number_fun, double x);

int generate_nodes(int t, double a, double b, int N, int number_fun, double *nodes, double *meanings);

int generate_equidistant_nodes(double a, double b, int N, int number_fun, double *nodes, double *meanings);
int generate_Chebyshev_nodes(double a, double b, int N, int number_fun, double *nodes, double *meanings);
int generate_random_nodes(double a, double b, int N, int number_fun, double *nodes, double *meanings);

void bubbleSort(double *nodes, int N);

void create_nodes2(double *nodes2, double *nodes, int N);
void create_new_nodes(double *new_nodes, double *nodes, double *new_meanings, double *meanings, int k, int N);

double s_algorithm(double *nodes, double *new_nodes, double *coef, double *meanings, double *new_meanings, int k, int N);

int toInt(const char *str, int *value);
int toDouble(const char *str, double *value);

#endif

