#include "functions.h"

double u(int number_u, double t, double x)
{
    switch(number_u)
    {
        case 0:
            return 0;
        case 1:
            return (x*x - 2*x) * exp(- PI * PI * t / 4);

        case 2:
            return (x*x*x-3.*x) * exp(- t);

        case 3:
            return (sin(PI*x/2)) * exp(- PI * PI * t / 4);
        
        case 4:
            return x * exp(- x) * exp(t);

        default:
            return 0;

    }
}

double u0(int number_u, double x)
{
    switch(number_u)
    {
        case 0:
            return 0;
        case 1:
            return x*x - 2*x;

        case 2:
            return x*x*x-3.*x;

        case 3:
            return sin(PI*x/2);
        
        case 4:
            return x * exp(- x);

        default:
            return 0;

    }
}

double p(double x)
{
    return 0 * x;
    //return exp(x);
}

double fun(int number_u, double t, double x)
{
    switch(number_u)
    {
        case 0:
            return 0;
        case 1:
            return exp(- PI * PI * t / 4) * ( - PI * PI * (x*x - 2*x) / 4 - 2);

        case 2:
            return -exp(- t) * (x*x*x + 3.*x);

        case 3:
            return 0;
        
        case 4:
            return 2 * exp(- x) * exp(t) + x * exp(t);

        default:
            return 0;

    }
}

int toInt(const char *str, int *value) 
{
    long result;
    char *e;
    errno = 0;
    result = strtol(str, &e, 10);

    if (errno != 0 || *e != '\0') 
        return -1;

    if (INT_MIN <= result && result <= INT_MAX) 
    {
        *value = (int) result;
        return 0;
    }
    return -1;
}

int toDouble(const char *str, double *value) 
{
    char *e;

    errno = 0;

    *value = strtod(str, &e);

    if (errno != 0 || *e != '\0') 
    {
        return -1;
    }

    return 0;
}
