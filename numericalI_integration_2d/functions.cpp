#include "functions.h"

double fun1(double x, double y){ return (x + y);}
double fun2(double x, double y){ return x * x + y * y;}
double fun3(double x, double y){ return (x * x * x * x + x * x * y * y + y * y * y *y);}
double fun4(double x, double y){ return x - y;}
double fun5(double x, double y){ return x * y;}



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
