#include "functions.h"

// implicit scheme - неявная схема

int sweep_method(double *a, double *b, double *c, double *f, double *y, double *alpha, double *beta, int N) 
{
    /* На самом деле, система должна иметь размер M+1, здесь обозначения из лекций Чижонкова*/
    alpha[0] = 0;
    beta[0] = 0;

    alpha[1] = b[0] / c[0];
    beta[1] = f[0] / c[0];
    for(int i = 1; i < N; i++)
    {
        alpha[i + 1] = b[i]                   / (c[i] - a[i] * alpha[i]);
        beta[i + 1] = (f[i] + a[i] * beta[i]) / (c[i] - a[i] * alpha[i]);
    }

    y[N] = (f[N] + a[N] * beta[N]) / (c[N] - a[N] * alpha[N]);

    for(int i = N - 1; i > -1; i--)
    {
        y[i] = alpha[i + 1] * y[i + 1] + beta[i + 1]; 
        // printf("y%d %lf  \n\n", i, y[i]);
    }
    return 1;
}

double error(double *previous_nodes, int number_u, int M) // |u*-u|
{
    // норма  - L_{2,h}
    double sum = 0.;
    double h = 1. / ((double)M - 0.5);

    for (int i = 1; i < M; i++)
    {
        sum += (previous_nodes[i] - u(number_u, 1, h * i)) * (previous_nodes[i] - u(number_u, 1, h * i));
    }

    sum = sum * h;

    return sqrt(sum);
}