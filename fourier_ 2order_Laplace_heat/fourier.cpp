#include "fourier.h"
#include "functions.h"

void create_phi(double *massive_phi, int m, int N) 
//записываем вектор \phi^m= (\phi_1^m, ...< \phi_(N-1)^m)
{
    double h = 1. / ((double)N - 0.5);
    for(int i = 1; i < N; i++)
    {
        massive_phi[i] = sin( PI * (2. * m - 1) * i * h/2);
    }
}

double scalar_product(double *massive_phi, double *massive_u, int N)
{
    double result = 0.;
    double h = 1. / ((double)N - 0.5);

    for(int j = 1; j < N; j++)
    {
        result += massive_phi[j] * massive_u[j] * h;
    }
    result = 2 * result;

    return result;
}

void make_coef_1d(double *massive_c, double *massive_u, double *massive_phi,  int N)
{
    double c = 0.;
    // Копируем значения функций в вспомогательный массив u
	for(int i = 0; i < N; i++)
	{
		massive_u[i] = massive_c[i];
	}
    for(int m = 1; m < N; m++)
    {
        create_phi(massive_phi, m, N);
        c = scalar_product(massive_phi, massive_u, N);
        massive_c[m] = c;
    } 
}

void fourier_to_c(double *massive_c, double *massive_phi, double *massive_u, int Nx, int Ny)
{
    double c = 0.;
    
    //считаем, что в массиве massive_c нам передается значение функции(которую надо разложить)
    // в узлах сетки


    //Применяем к каждой строке последовательно алгоритм для случая 1d
    for(int j = 0; j < Ny; j++)
    {
        make_coef_1d(massive_c + (j) * (Nx), massive_u, massive_phi, Nx);
    }

    //Получили матрицу D
    //Дальше применяем по столбцам
	for(int k = 0; k < Nx; k++)
	{
		for(int m = 0; m < Ny; m++)
		{
			massive_u[m] = massive_c[(m) * (Nx) + k];
		}

		for(int n = 1; n < Ny; n++)
		{
            // создаем psi
			create_phi(massive_phi, n, Ny);
			c = scalar_product(massive_phi, massive_u, Ny);
			massive_c[(n) * (Nx) + k] = c;
		}
	}
}

double back_fourier(double *massive_c, double x, double y, int Nx, int Ny)
{
    double result = 0.;

    for(int j = 1; j < Ny; j++)
    {
        for(int i = 1; i < Nx; i++)
        {
            result += massive_c[(j) * (Nx) + i] * sin(PI * (i - 0.5) * x) * sin(PI * (j - 0.5) * y);
        }   
    }
    return result;
}

double error(double *matrix_c, int number_u, int Nx, int Ny, double T) //максимум разности на последнем слое
{
    double hx = 1. / ((double)(Nx) - 0.5);
    double hy = 1. / ((double)(Ny) - 0.5);

    double x = 0., y = 0.;
    double res = 0., max = 0.;
    for(int i = 1; i < Nx; i++)
        for(int j = 1; j < Ny; j++)
        {
            x = i * hx;
            y = j * hy;
            res = fabs(u(number_u, T, x, y) - back_fourier(matrix_c, x, y, Nx, Ny));
            if(res > max)
                max = res;
        }
    return max;
}

double error_plus(double *matrix_c, int number_u, int Nx, int Ny, double T, int *i_max, int *j_max) //максимум разности на последнем слое
{
    double hx = 1. / ((double)(Nx) - 0.5);
    double hy = 1. / ((double)(Ny) - 0.5);

    (void)i_max;
    (void)j_max;
    double x = 0., y = 0.;
    double res = 0., max = 0.;
    for(int i = 1; i < Nx; i++)
        for(int j = 1; j < Ny; j++)
        {
            x = i * hx;
            y = j * hy;
            res = fabs(u(number_u, T, x, y) - back_fourier(matrix_c, x, y, Nx, Ny));
            if(res > max)
            {
                max = res;
                *i_max = i;
                *j_max = j;
            }

        }
    return max;
}

