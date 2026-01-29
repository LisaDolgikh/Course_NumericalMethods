#ifndef _RICHARDSON_H_    
#define _RICHARDSON_H_

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

double method_richardson(double *x, double *A, double *b, double tau, int N, int mIter, double *mem);
double find_tau(double *A, int N);



#endif