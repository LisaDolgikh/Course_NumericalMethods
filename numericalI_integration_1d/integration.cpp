#include "integration.h"

//метод прямоугольников
double rectangle_method(double a, double b, double (*f)(double))
{
    double x_0 = (a + b) / 2.;

    return (b - a) * f(x_0);

}

//метод Симпсона
double simpson_method(double a, double b, double (*f)(double))
{
    return ((b - a) * (f(a) + 4 * f((a + b) / 2.) + f(b)) / 6.);
}


//метод Гаусса
double gauss_method(double a, double b, double (*f)(double))
{
    double x_0 = (a + b) / 2;
    double x_minus = x_0 - (b - a) * sqrt(3. / 5.) / 2.;
    double x_plus = x_0 + (b - a) * sqrt(3. / 5.) / 2.;

    return (b - a) * (5 * f(x_minus) + 8 * f(x_0) + 5 * f(x_plus)) / 18.;
}

//составная квадратура прямоугольников
double composite_rectangle_method(double a, double b, double (*f)(double), int N)
{
    double step = (b - a) / N;
    double ans = 0.;

    for(int i = 0; i < N; i++) 
    {
        ans += rectangle_method(a + i * step, a + (i + 1) * step, f);
    } 

    return ans;
}

// составная квадратура Симпсона
double composite_simpson_method(double a, double b, double (*f)(double), int N)
{
    double step = (b - a) / N;
    double ans = 0.;

    for(int i = 0; i < N; i++) 
    {
        ans += simpson_method(a + i * step, a + (i + 1) * step, f);
    } 

    return ans;
}

// составная квадратура Гаусса
double composite_gauss_method(double a, double b, double (*f)(double), int N)
{
    double step = (b - a) / N;
    double ans = 0.;

    for(int i = 0; i < N; i++) 
    {
        ans += gauss_method(a + i * step, a + (i + 1) * step, f);
    } 

    return ans;
}
