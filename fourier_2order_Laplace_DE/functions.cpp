#include "functions.h"

double fun(int number_fun, double x)
{
    switch(number_fun)
    {
        case 0:
            return 1;
        case 1:
            return x*x - 2*x;

        case 2:
            return x*x*x-3.*x;

        case 3:
            return sin(PI*x/2);

        case 4:
            return 1/(double)(1.+25.*(x-1)*(x-1)) - 1./26.;

        case 5:
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
