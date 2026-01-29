#include "bsolver.h"
#include "richardson.h"
#include "fourier.h"
#include "functions.h"
#include "matrix.h"

double method_BSolver(double *x, double *A, double *B, double *b, double tau, int N, int mIter, double *mem, double *mem1)
{
    for (int k = 0; k < N; k++)
    {
        x[k] = 0;
        mem[k] = 0;
    }
    for (int m = 0; m < mIter; m++)
    {
        mult_matrix_vector(A, x, mem, N);
        for (int j = 0; j < N; j++)
            mem[j] = b[j] - mem[j];
        
        //Матрицу B мы уже изначально создавали как обратную
        mult_matrix_vector(B, mem, mem1, N);

        for (int i = 0; i < N; i++)
        {
            x[i] = x[i] + tau * mem1[i];
        }
    }
    return residual(A, b, x, N);
    //return error(A, b, x, N); //||Ax - b||
}

double find_q0(double *A, int N)
{
    double max = 0.;
    double min = 0.;
    double sum = 0.;
    for (int i = 0; i < N; i++)
    {
        sum = 0.;
        for (int j = 0; j < N; j++)
        {
            sum += fabs(A[i * (N) + j]);
        }
        if(i == 0)
            min = 2 * A[i * (N) + i] - sum;
        
        if (sum > max)
            max = sum;

        if (2 * A[i * (N) + i] - sum < min)
            min = 2 * A[i * (N) + i] - sum;
    }
    return (double)(max - min) / (double)(max + min);
}

void make_matrix_3(double *A, int N, double p) 
{
    double tmp;

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {

            if (i == j)
            {
                //tmp = sin(PI * (2 * i + 1) / (double)(2 * N + 1));
                tmp = sin(PI * (i + 1) / (double)(N + 0.5));
                A[i * (N) + j] = p + 2 * (N + 0.5) * (N + 0.5) + 1 + tmp * tmp;
            }
            else if (i - j == 1 || i - j == -1)
                A[i * (N) + j] = -1.0 * (N + 0.5) * (N + 0.5);
            else
                A[i * (N) + j] = 0;
        }
        tmp = sin(PI * (N) / (double)(N + 0.5));
        A[(N - 1) * (N) + N - 1] = (N + 0.5) * (N + 0.5) + p + 1 + tmp*tmp;
    }
}

void reverse_fourier_matrix_without_0(double p, double *B, int N, double *mem1, double *mem2) 
{
    for(int i = 0; i < N + 1; i++) 
    {
        mem2[i] = 0.;
    }
    for(int i = 1; i < N; i++) 
    {   
        mem2[i] = 1.;
        //void method_fourier(double *y, int N, double p, double *f);
        method_fourier(mem1, N, p, mem2);
        mem2[i] = 0.;
        for(int j = 0; j < N - 1; j++) 
        {
            B[j + (i - 1) * (N - 1)] = mem1[j + 1];
        }
    }
}
