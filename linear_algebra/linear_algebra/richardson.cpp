#include "richardson.h"
#include "fourier.h"
#include "functions.h"
#include "matrix.h"

double method_richardson(double *x, double *A, double *b, double tau, int N, int mIter, double *mem)
{
    for (int k = 0; k < N; k++)
    {
        x[k] = 0.;
        mem[k] = 0.;
    }
    for (int m = 0; m < mIter; m++)
    {
        mult_matrix_vector(A, x, mem, N);

        for (int i = 0; i < N; i++)
        {
            x[i] = x[i] - tau * mem[i] + tau * b[i];
        }
    }

    return residual(A, b, x, N); //||Ax - b||
}

double find_tau(double *A, int N)
{
    double max = 0.;
    double min = 0.;
    double sum = 0.;
    for (int i = 0; i < N; i++)
    {
        sum = 0.;
        for (int j = 0; j < N; j++)
        {
            sum += fabs(A[i * N + j]);
        }
        if (sum > max)
            max = sum;

        if (2 * A[i * N + i] - sum < min)
            min = 2 * A[i * N + i] - sum;
    }
    return 2. / (max + min);
}