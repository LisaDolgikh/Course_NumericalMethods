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

//метод прямоугольников
double rectangle_method(double a, double b, double (*f)(double));

// метод Симпсона
double simpson_method(double a, double b, double (*f)(double));

// метод Гаусса
double gauss_method(double a, double b, double (*f)(double));


//составная квадратура прямоугольников
double composite_rectangle_method(double a, double b, double (*f)(double), int N);

// составная квадратура Симпсона
double composite_simpson_method(double a, double b, double (*f)(double), int N);

// составная квадратура Гаусса
double composite_gauss_method(double a, double b, double (*f)(double), int N);

#endif
