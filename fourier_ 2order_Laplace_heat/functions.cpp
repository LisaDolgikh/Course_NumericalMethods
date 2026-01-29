#include "functions.h"

double u(int number_u, double t, double x, double y)
{
    switch(number_u)
    {
        case 0:
            return 0;
        case 1:
            return (x*x - 2*x) * (y*y - 2*y)* exp(- PI * PI * t / 4);

        case 2:
            return (sin(PI*x/2)) * (sin(PI*y/2)) * exp(- PI * PI * t / 2);
        
        case 3:
        {
            int m = 1;
            int n = 2;
            return (sin(PI/2 * (2*m - 1) * x)) * (sin(PI/2 * (2*n - 1) * y)) * exp(- PI * PI * t/ 4 * ((2*m-1) *(2*m-1) + (2*n-1) *(2*n-1)));
        }

        default:
            return 0;

    }
}

double u0(int number_u, double x, double y)
{
    switch(number_u)
    {
        case 0:
            return 0;
        case 1:
            return (x*x - 2*x) * (y*y - 2*y);

        case 2:
            return sin(PI*x/2) * sin(PI*y/2);

        case 3:
        {
            int m = 1;
            int n = 2;
            return (sin(PI/2 * (2*m - 1) * x)) * (sin(PI/2 * (2*n - 1) * y));
        }

        default:
            return 0;

    }
}

double p(double x, double y)
{
    return 0 * x * y;
    //return exp(x);
}

double fun(int number_u, double t, double x, double y)
{
    switch(number_u)
    {
        case 0:
            return 0;
        case 1:
            return exp(- PI * PI * t / 4) * ( - PI*PI/4*(x*x - 2*x) * (y*y - 2*y) - 2*(x*x - 2*x) - 2*(y*y - 2*y));

        case 2:
            return 0;

        case 3:
            return 0;

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
