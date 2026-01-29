#include "fourier.h"

double fun(int number_fun, double x, double y)
{
    switch(number_fun)
    {
        case 1:
            return sin(x * PI / 2) * sin(y * PI / 2);

        case 2:
            return (x*x - 2*x) * (y*y - 2*y);

        case 3:
            return (x*x*x - 3*x) * (y*y*y - 3*y);

        case 4:
            return (1 - cos(PI * x)) * (1 - cos(PI * y));

        case 5:
            return (exp(x) - exp(1) * x - 1) * (log(1 + x*x) - 2 * log(1 + x)) * (x*x - 2*x) * (exp(y) - exp(1) * y - 1) * (log(1 + y*y) - 2 * log(1 + y)) * (y*y - 2*y);

        case 6:
			if((x > 0.4) && (x < 0.6) && (y > 0.4) && (y < 0.6))
				return 1.;
			else
				return 0.;

        default:
            return 0;

    }
}

void make_points(double *massive_dots, int N)
{
    double h = 1. / ((double)N - 0.5);
    double tmp = 0.;

    for (int i = 0; i < N + 1; i++)
    {
        massive_dots[i] = tmp;
        tmp += h;
    }
}

void create_phi(double *massive_phi, int k, int N) 
//записываем вектор \phi^k= (\phi_1^k, ...< \phi_(N-1)^k)
{
    double h = 1. / ((double)N - 0.5);
    for(int j = 0; j < N+1; j++)
    {
        massive_phi[j] = sin( PI * (2. * k - 1) * j * h/2);
    }
}

double scalar_product(double *massive_phi, double *massive_u, int N)
{
    double result = 0.;
    //double norma = 0.;
    double h = 1. / ((double)N - 0.5);
    for(int j = 1; j < N; j++)
    {
        result += massive_phi[j] * massive_u[j] * h;
        //norma += massive_phi[j] * massive_phi[j] * h;
    }

    //result = result / (double)norma;
    //std::cout << norma  << std::endl;
    result = 2 * result;

    return result;
}

void make_coef_1d(double *massive_c, double *massive_u, double *massive_phi,  int N)
{
    double c = 0.;
    // Копируем значения функций в вспомогательный массив u
	for(int k = 0; k < N; k++)
	{
		massive_u[k] = massive_c[k];
	}
    for(int k = 1; k < N; k++)
    {
        create_phi(massive_phi, k, N);
        c = scalar_product(massive_phi, massive_u, N);
        massive_c[k] = c;
    }
}
   

void fourier_to_c(double *massive_c, double *massive_phi, double *massive_u, double *massive_dots, int number_fun, int N)
{
    double c = 0.;
    make_points(massive_dots, N);

    //сохраняем u на месте коэффициентов
    make_fun(massive_c, massive_dots, number_fun, N);

    //Применяем к каждой строке последовательно алгоритм для случая 1d
    for(int k = 0; k < N; k++)
    {
        make_coef_1d(massive_c + k*N, massive_u, massive_phi, N);
    }

    //Получили матрицу D
    //Дальше применяем по столбцам
	for(int k = 0; k < N; k++)
	{
		for(int m = 0; m < N; m++)
		{
			massive_u[m] = c(m, k, N);
		}

		for(int n = 1; n < N; n++)
		{
			create_phi(massive_phi, n, N);
			c = scalar_product(massive_phi, massive_u, N);
			c(n, k, N) = c;
		}
	}
}

void make_fun(double *massive_c, double *massive_dots, int number_fun, int N)
{
    for(int i = 0; i < N; i++)
        for(int j = 0; j < N; j++)
            c(i, j, N) = fun(number_fun, massive_dots[i], massive_dots[j]);
}

double back_fourier(double *massive_c, double x, double y, int N)
{
    double result = 0.;

    for(int i = 1; i < N; i++)
    {
        for(int j = 1; j < N; j++)
        {
            result += c(i, j , N) * sin(PI * (i - 0.5) * x) * sin(PI * (j - 0.5) * y);
        }   
    }
    return result;
}

double norma(double *massive_c, int number_fun, int N)
{
    double h = 1. / ((double)(2 * N) - 0.5);
    double x = 0., y = 0.;
    double res = 0., max = 0.;
    for(int i = 1; i <= 2 * N; i++)
        for(int j = 1; j <= 2 * N; j++)
        {
            if(j%2 == 0)
            {
                continue;
            }
            x = i * h;
            y = j * h;
            res = fabs(fun(number_fun, x, y) - back_fourier(massive_c, x, y, N));
            if(res > max)
                max = res;
        }
    return max;
}
