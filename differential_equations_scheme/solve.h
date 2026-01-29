#ifndef _SOLVE_H_    
#define _SOLVE_H_

#include <stdlib.h>
#include <math.h>
#include <stdio.h>

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

double solution_1(double y0, double A, int N);
double solution_2(double y0, double A, int N);
double solution_3(double y0, double A, int N);
double solution_4(double y0, double A, int N);

double ans(double A, double y0, double x); 
double norm(double theor_y, double y);

#endif