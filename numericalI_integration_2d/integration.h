#ifndef _INTEGRATION_H_    
#define _INTEGRATION_H_

#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <cstring>
#include <cmath>
#include <cerrno>
#include <climits>

double integrate(int N, double (*f)(double, double), double *nodes_x, double *nodes_y, int *triangle_1, int *triangle_2, int *triangle_3);

#endif
