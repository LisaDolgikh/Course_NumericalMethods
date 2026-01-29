#include "approximation.h"
// int t = тип узлов: 0 - равноудаленные, 1 - чебышевские, 2 - случайные
// 0: всё ок
// -1: недотстаточно узлов
// -2: некоректные границы

double fun(int number_fun, double x)
{
    switch(number_fun)
    {
        case 1:
            return pow(x,4) + 3 * pow(x,3) + x*x - 10;
        case 2:
            return pow(E, x);

        case 3:
            return 1 / (1 + 25 * x * x);

        case 4:
            return -x * (x < 0) + x * (x > 0);

        case 5:
	    if(x > 0.3 && x < 0.6)
		    return 1.;
	    else
		    return 0.;
            /*return log(x * x + x + 3);*/

        default:
            return 0;

    }
}

int generate_nodes(int t, double a, double b, int N, int number_fun, double *nodes, double *meanings)
{
    int res = 0;
    if(t == 0)
    {
        std::cout << "Equidistant nodes generated" << std::endl;
        res = generate_equidistant_nodes(a, b, N, number_fun, nodes, meanings);
            
    }
    else if(t == 1)
    {
        std::cout << "Chebyshev nodes generated" << std::endl;
        res = generate_Chebyshev_nodes(a, b, N, number_fun, nodes, meanings);
    }
    else // (t == 2)
    {
        std::cout << "Random nodes generated" << std::endl;
        res = generate_random_nodes(a, b, N, number_fun, nodes, meanings);
            
    }

    return res;
}
int generate_equidistant_nodes(double a, double b, int N, int number_fun, double *nodes, double *meanings)
{
    if(N <= 1) 
        return -1;
    if(N == 2)
    {
        nodes[0] = a; 
        nodes[1] = b;
        meanings[0] = fun(number_fun, a);
        meanings[1] = fun(number_fun, b);
        return 0;
    } 
    if(a > b)
        return -2;

    double h = (b - a) / double(N - 1);
    double tmp = a;
    for(int i = 0; i < N; ++i) 
    {
        nodes[i] = tmp;
        meanings[i] = fun(number_fun, tmp);
        tmp += h;
    }
    return 0;
} 

int generate_Chebyshev_nodes(double a, double b, int N, int number_fun, double *nodes, double *meanings)
{
    if(N <= 1)
        return -1;
    if(a > b)
        return -2;

    double h1 = (b + a) / 2.;
    double h2 = (b - a) / 2.;

    for(int i = 0; i < N; ++i) 
    {
        nodes[N - 1 - i] = h1 + h2* cos((2 * i + 1) * PI / (2 * N));
        meanings[N - 1 - i] = fun(number_fun, nodes[N - 1 - i]);
    }
    return 0;
} 

int generate_random_nodes(double a, double b, int N, int number_fun, double *nodes, double *meanings)
{
    int randint;
    srand(0);
	for(int i = 0; i < N; i++)
	{
		randint = rand();
			
		nodes[i] = a + (b - a) * ((double) randint / RAND_MAX);
	}

	bubbleSort(nodes, N);

    for(int i = 0; i < N; i++)
    {
        meanings[i] = fun(number_fun, nodes[i]);
    }
   
    return 0;
}

void bubbleSort(double *nodes, int N)
{
    int flag;

    for(int k = N; k > 1; k--)
    {
        flag = 1;

        for(int i = 0; i < (k-1); i++)
        {
            if(nodes[i] > nodes[i+1])
            {
				double tmp = *(nodes + i);
				*(nodes + i) = *(nodes + i + 1);
				*(nodes + i + 1) = tmp;
                flag = 0;
            }
        }
        if(flag)               
			return;
    }
}

void create_nodes2(double *nodes2, double *nodes, int N)
{
    double h = 0.;
    for(int i = 0; i < N - 1; i++)
    {
        h = (nodes[i + 1] - nodes[i]) / 2.;
        nodes2[2 * i] = nodes[i];
        nodes2[2 * i + 1] = nodes[i] + h;
    }
    nodes2[2 * (N - 1)] = nodes[N - 1];
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


