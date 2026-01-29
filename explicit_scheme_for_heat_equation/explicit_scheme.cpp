#include "functions.h"

// explicit scheme - явная схема


void find_current_nodes(double *previous_nodes, double *current_nodes, int N, int M, int n, int number_u)
{
    double h = 1. / ((double)M - 0.5);
    double tau = 1. / (double)(N - 1);
    double tmp = tau * ((double)M - 0.5) * ((double)M - 0.5);

    for(int m = 1; m < M; m++)
    {
        current_nodes[m] = tmp * previous_nodes[m - 1] - (2. * tmp - 1 + tau * p(m * h)) * previous_nodes[m] + tmp * previous_nodes[m + 1] + tau * fun(number_u, n * tau, m * h);
    }
    current_nodes[0] = 0.;
    current_nodes[M] = current_nodes[M - 1];
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