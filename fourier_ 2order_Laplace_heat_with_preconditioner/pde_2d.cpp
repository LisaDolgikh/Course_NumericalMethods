#include "functions.h"
#include "fourier.h"

void make_d_from_f(double *matrix_d, double *massive_phi, double *massive_u, int Nx, int Ny, int number_u, double time)
{
    double hx = 1. / ((double)Nx - 0.5);
    double hy = 1. / ((double)Ny - 0.5);
    
    //считаем правую часть
    for(int j = 0; j < Ny; j++)
    {
        for(int i = 0; i < Nx; i++)
        {
            matrix_d[(j) * (Nx) + i] = fun(number_u, time, hx * i, hy * j);
        }
    }

    // раскладываем эту правую часть в двумерный ряд Фурье
    fourier_to_c(matrix_d, massive_phi, massive_u, Nx, Ny);
}


double lambda_m(int m, int N)
{
    double tmp = sin((PI / 2.) * (2 * m - 1) / (double)(2 * N - 1));
    double l = 4 * (N - 0.5) * (N - 0.5) * tmp * tmp;

    return l;
}

void make_c_from_d_and_previous(double *matrix_d, double *matrix_c, double *previous_nodes, int Nx, int Ny, double tau, double p_const)
{
    for(int n = 1; n < Ny; n++)
    {
        for(int m = 1; m < Nx; m++)
        {
            //matrix_c[(n) * (Nx) + m] = (matrix_d[(n) * (Nx) + m] + (previous_nodes[(n) * (Nx) + m] / tau)) / (lambda_m(m, Nx) + lambda_m(n, Ny) + p_const + (1. / tau));
            matrix_c[(n) * (Nx) + m] = (matrix_d[(n) * (Nx) + m] * tau + (previous_nodes[(n) * (Nx) + m])) / ((lambda_m(m, Nx) + lambda_m(n, Ny) + p_const)*tau + 1.);
        }
    }
}
