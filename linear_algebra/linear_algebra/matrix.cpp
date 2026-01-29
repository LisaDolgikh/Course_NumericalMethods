#include "matrix.h"

void print_matrix_1(double * A, int N) 
{
    for(int i = 0; i < N * N; i++) 
    {
        if(i % N == 0) 
            std::cout << " ... " << std::endl;
        std::cout << A[i];
    }
    std::cout << " ... " << std::endl;
}

void print_matrix(double *matrix, int size, int maxPrintSize)
{
    int printSize = (size < maxPrintSize) ? size : maxPrintSize;

    for (int i = 0; i < printSize; i++) 
    {
        for (int j = 0; j < printSize; j++) 
        {
            printf("%lf ", matrix[i * size + j]);
        }

        if (printSize != size) 
        {
            printf("... ");
        }
        printf(" \n");
        //std::cout << " ... " << std::endl;
    }

    if (printSize != size) 
    {
        printf("...\n");
    }
}

void mult_matrix_vector(double *A, double *x, double *ans, int N)
{
    for (int i = 0; i < N; i++)
    {
        ans[i] = 0.;
        for (int j = 0; j < N; j++)
        {
            ans[i] += A[i * N + j] * x[j];
        }
    }
}

void print_system(double *matrix, double *rhs, int size, int maxPrintSize)
{
    int printSize = (size < maxPrintSize) ? size : maxPrintSize;

    for (int i = 0; i < printSize; i++) 
    {
        for (int j = 0; j < printSize; j++) 
        {
            printf("%+.2e ", matrix[i * size + j]);
        }

        if (printSize != size) 
        {
            printf("... ");
        }

        printf("| %+.2e\n", rhs[i]);
    }

    if (printSize != size) 
    {
        printf("...\n");
    }
}

void print_vector(double *vector, int size, int maxPrintSize)
{
    int printSize = (size < maxPrintSize) ? size : maxPrintSize;

    printf("(");

    for (int i = 0; i < printSize; i++) 
    {
        printf("%lf ", vector[i]);
    }

    if (printSize != size) 
    {
        printf("...");
    }

    printf(")^t\n");
}

double residual(double *matrix, double *rhs, double *result, int size) // |Ax*-B|
{
    double resultSquared = 0.;
    double tmp;

    for (int i = 0; i < size; i++)
    {
        tmp = 0.;

        for (int j = 0; j < size; j++)
        {
            tmp += matrix[i * size + j] * result[j];
        }

        tmp -= rhs[i];

        resultSquared += tmp * tmp;
    }

    return sqrt(resultSquared);
}

double error(double *matrix, double *rhs, double *result, int size)
{
    double ans = 0.;
    double tmp;

    for (int i = 0; i < size; i++)
    {
        tmp = 0.;

        for (int j = 0; j < size; j++)
        {
            tmp += matrix[i * size + j] * result[j];
        }

        tmp -= rhs[i];
        if(fabs(tmp) > ans)
            ans = fabs(tmp);
    }

    return sqrt(ans);
}

int read_matrix(FILE *finput, double *matrix, int size)
{
    for (int i = 0; i < size * size; i++)
    {
        fscanf(finput, "%lf", &matrix[i]);
    }
    return 1;
}
