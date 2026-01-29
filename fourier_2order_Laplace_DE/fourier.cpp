#include "fourier.h"
#include "functions.h"
#include "matrix.h"

void make_b_from_A(double *A, int N, double *b)
{
    for (int k = 0; k < N; k++)
    {
        b[k] = 0.;
        for (int j = 0; j < N; j++)
        {
            b[k] += A[k * (N) + j];
        }
    }
}

void make_b_from_x(double p, double *x, int N, double *b)
// Написать создание столбца b из x
{
    double h_reverse = (double)N - 0.5;  // h^(-1)
    double h_reverse_square = h_reverse * h_reverse;

    for(int i = 1; i < N - 2; i++)
    {
        b[i] = 0.;
        b[i] += (2 * h_reverse_square + p) * x[i];
        b[i] -= h_reverse_square * x[i - 1];
        b[i] -= h_reverse_square * x[i + 1];
    }

    b[0] = (2 * h_reverse_square + p) * x[0] - h_reverse_square * x[1];
    b[N - 2] = (h_reverse_square + p) * x[N - 2] - h_reverse_square * x[N - 3];
}

void make_b_from_f(double *b, int N, int number_fun)
{
    double h = 1. / ((double)N - 0.5);
    double xk = h;
    for (int k = 0; k < N - 1; k++)
    {
        xk = (k + 1) * h;
        b[k] = fun(number_fun, xk );
    }
}

void make_fourier_matrix(double *A, int N, double p)
{
    double h_reverse = (double)N - 0.5;  // h^(-1)
    double h_reverse_square = h_reverse * h_reverse;

    for(int i = 0; i < N - 1 ; i++)
    {
        for(int j = 0; j < N - 1; j++)
        {
            if(i == j)
                A[i * (N - 1) + j] = p + 2.0 * h_reverse_square;
            else if (i - j == 1 || i - j == -1)
                A[i * (N - 1) + j] = -1.0 * h_reverse_square;
            else
                A[i * (N - 1) + j] = 0.;
        }
    }
    A[(N - 2) * (N - 1) + N - 2] = h_reverse_square + p ;

}

void method_fourier(double *y, int N, double p, double *f)
{
    for (int k = 0; k < N + 1; k++)
    {
        y[k] = 0;
        for (int m = 1; m < N; m++)
        {
            y[k] += d_m(m, f, N) / lambda_m(m, N, p) * psi(k, m, N);
        }
    }
}

double psi(int k, int m, int N) //\psi_k^m
{
    return sin(PI * k * (2 * m - 1) / (double)(2 * N - 1));
}

double lambda_m(int m, int N, double p)
{
    //double tmp = sin((PI / 2.) * (2 * m - 1) / (double)(2 * N - 1));
    //double l = p + 4 * (N - 0.5) * (N - 0.5) * tmp * tmp;
    double l = p - 2 * (N - 0.5) * (N - 0.5) * (cos(PI * (2 * m - 1) / (double)(2 * (N) - 1)) - 1);
    return l;
}

double d_m(int m, double *f, int N)
{
    double h = 1. / ((double)N - 0.5);
    double tmp = 0.;
    for (int i = 1; i < N; i++) //тут было с 0
    {
        tmp += 2 * f[i] * psi(i, m, N) * h;
    }

    return tmp;
}

