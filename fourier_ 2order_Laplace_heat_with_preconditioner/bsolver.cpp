#include "fourier.h"
#include "functions.h"

void method_BSolver(double *old_matrix_u, double *vector_b, int Nx, int Ny, double tau, double theta, double p_const, double *massive_phi, double *massive_u, double *matrix_c, double *matrix_u)
{
    double hx = 1. / ((double)Nx - 0.5);
    double hy = 1. / ((double)Ny - 0.5);
    // old_matrix_u    -   u^{n+1, k}
    // matrix_u        -   u^{n+1, k+1}
    // previous_nodes  -   u^n
    double error = 100.;
    int iterations = 1;

    //В матрице old_matrix_u передаем значения u^{n+1,0}
    //вычисленные без использования предобуславливателя

    while(iterations < 50 && error > 1e-9)
    {
        // Au
        mult_matrix_Au(old_matrix_u, matrix_u, tau, Nx, Ny);

        for(int j = 0; j < Ny; j++)
        {
            for(int i = 0; i < Nx; i++)
            {
                // b - Au
                int index = (j) * (Nx) + i;
                matrix_u[index] = vector_b[index] - matrix_u[index];
            }
        }

        // решаем систему Фурье By=f
        // f записан в matrix_u

        // раскладываем эту f в ряд Фурье
        fourier_to_c(matrix_u, massive_phi, massive_u, Nx, Ny);

        // находим коэффициенты Фурье нашего вектора y
        make_c_from_f(matrix_u, matrix_c, Nx, Ny, tau, p_const);
        
        // Восстанавливаем значения вектора y из коэффициентов  Фурье
        for(int j = 0; j < Ny; j++)
        {
            for(int i = 0; i < Nx; i++)
            {
                int index = (j) * (Nx) + i;
                matrix_u[index] = back_fourier(matrix_c, i * hx, j * hy, Nx, Ny);
            }
        } 

        // из y восстанавливаем u^{n+1, k+1}
        for(int j = 0; j < Ny; j++)
        {
            for(int i = 0; i < Nx; i++)
            {
                int index = (j) * (Nx) + i;
                old_matrix_u[index] = old_matrix_u[index] + theta * matrix_u[index];
            }
        }

        //Считаем невязку
        error = 0.;

        mult_matrix_Au(old_matrix_u, matrix_u, tau, Nx, Ny);
        for (int j = 0; j < Ny; j++)
        {
            for (int i = 0; i < Nx; i++)
            {
                double tmp = 0.;
                int index = (j) * (Nx) + i;
                tmp = fabs(matrix_u[index] - vector_b[index]);
                //error += tmp * tmp;
                if(tmp > error)
                {
                    error = tmp;
                }

            }
        }
        //error = sqrt(error);

        //printf("n_iter = %d residual = %e \n", iterations, error);
        iterations++;
    }
    //return residual(A, b, x, N);
    //return error(A, b, x, N); //||Ax - b||
}

void mult_matrix_Au(double *matrix_u, double *res_u, double tau, int Nx, int Ny)
{
    double hx = 1. / ((double)Nx - 0.5);
    double hy = 1. / ((double)Ny - 0.5);

    double hx_reverse = (double)Nx - 0.5;  // hx^(-1)
    double hx_reverse_square = hx_reverse * hx_reverse;

    double hy_reverse = (double)Ny - 0.5;  // hy^(-1)
    double hy_reverse_square = hy_reverse * hy_reverse;

    double tmp = 2 * hx_reverse_square + 2 * hy_reverse_square + 1. / tau;

    //i = 1, j = Ny -2;

    //случай  j = 0
    for(int i = 0; i < Nx; i++)
    {
        res_u[i] = matrix_u[i];
    }

    for(int j = 1; j < Ny - 1; j++)
    {
        // случай i = 0;
        res_u[(j) * (Nx)] = matrix_u[(j) * (Nx)];

        for(int i = 1; i < Nx - 1; i++)
        {
            res_u[(j) * (Nx) + i] = - hy_reverse_square * matrix_u[(j - 1) * (Nx) + i] - hx_reverse_square * matrix_u[(j) * (Nx) + i - 1] + tmp * matrix_u[(j) * (Nx) + i] - hx_reverse_square * matrix_u[(j) * (Nx) + i + 1] - hy_reverse_square * matrix_u[(j + 1) * (Nx) + i];
            res_u[(j) * (Nx) + i] += p(i * hx, j * hy) * matrix_u[(j) * (Nx) + i];
        }

        //случай i = Nx-1
        res_u[(j) * (Nx) + Nx - 1] = - hy_reverse_square * matrix_u[(j - 1) * (Nx) + Nx - 1] - hx_reverse_square * matrix_u[(j) * (Nx) + Nx - 2] + (tmp - hx_reverse_square + p((Nx-1)*hx, j*hy)) * matrix_u[(j) * (Nx) + Nx - 1] - hy_reverse_square * matrix_u[(j + 1) * (Nx) + Nx - 1];
    }

    // случай i = 0; j = Ny - 1
    res_u[(Ny - 1) * (Nx) ] = matrix_u[(Ny - 1) * (Nx)];
    // последний слой (когда j = Ny-1)
    for(int i = 1; i < Nx - 1; i++)
    {
        res_u[(Ny - 1) * Nx + i] = - hy_reverse_square * matrix_u[(Ny - 2) * (Nx) + i] - hx_reverse_square * matrix_u[(Ny - 1) * (Nx) + i - 1] + (tmp - hy_reverse_square + p(i* hx,(Ny-1) * hy)) * matrix_u[(Ny - 1) * (Nx) + i] - hx_reverse_square * matrix_u[(Ny - 1) * (Nx) + i + 1];
    }
    res_u[(Ny - 1) * Nx + Nx - 1] = - hy_reverse_square * matrix_u[(Ny - 2) * (Nx) + Nx - 1] - hx_reverse_square * matrix_u[(Ny - 1) * (Nx) + Nx - 2] + (tmp - hy_reverse_square - hx_reverse_square + p((Nx-1)*hx, (Ny-1)*hy)) * matrix_u[(Ny - 1) * (Nx) + Nx - 1];
}

void make_c_from_f(double *matrix_f, double *matrix_c, int Nx, int Ny, double tau, double p_const)
{
    (void) p_const;
    (void) tau;
    for(int n = 0; n < Ny; n++)
    {
        for(int m = 0; m < Nx; m++)
        {
            matrix_c[(n) * (Nx) + m] = (matrix_f[(n) * (Nx) + m])/ (lambda_m(m, Nx) + lambda_m(n, Ny) + p_const + (1. / tau));
        }
    }
}