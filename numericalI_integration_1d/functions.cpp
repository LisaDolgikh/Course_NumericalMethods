#include "functions.h"

double fun0(double x){ return 1 + x * 0;}
double fun1(double x){ return 2 * x;}
double fun2(double x){ return 3 * x * x;}
double fun3(double x){ return 4 * x * x * x;}
double fun4(double x){ return exp(x);}
double fun5(double x){ return x * exp(x);}
double fun6(double x){ return cos(100*x);} // I[0, PI] = 0
double fun7(double x){ return exp(-1000 * x);} // I[0,1] = 10^(-3) 
double fun8(double x){ return 1 / sqrt(x);}
double fun9(double x){ return 1 / sqrt(1 - x * x);} // I[-1, 1] = PI


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
