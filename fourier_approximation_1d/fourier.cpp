#include "fourier.h"

int make_points(int N, double *massive_dots)
{
    double h = 1. / ((double)N - 0.5);
    double tmp = h;
    
    if (N <= 2)
    {
        std::cout << "Not enough points" << std::endl;
        return -1;
    }
        
    massive_dots[0] = 0.;
    massive_dots[N] = 1. + h/2.;

    for (int i = 1; i < N; i++)
    {
        massive_dots[i] = tmp;
        tmp += h;
    }

    return 0;
}

void phi(double *massive_phi, int k, int N) 
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

int make_coef(double *massive_ck, double *massive_u, double *massive_phi,  int N)
{
    double ck = 0.;
    for(int k = 1; k < N; k++)
    {
        phi(massive_phi, k, N);
        ck = scalar_product(massive_phi, massive_u, N);
        massive_ck [k] = ck;
    }

    return 0;
}

double back_fourier(double *massive_ck, double x, int N)
{
    double result = 0.;

    for(int k = 1; k < N; k++)
    {
        result += massive_ck[k] * sin(PI * (k - 0.5) * x);
    }
    return result;
}

double search_norma(double *massive_ck, int number_fun, int N)
{
	double result = 0., h = 1. / (2 * ((double)N - 0.5));
    double tmp = 0.;


	for(int k = 0; k <= 2 * N; k++)
	{
		tmp = fabs(u(number_fun, (k * h)) - back_fourier(massive_ck, (k * h), N));
        if (tmp > result)
            result = tmp;
	}

	return result;
}

double error_fourier(double *massive_ck, double *massive_dots, double *massive_u, double *massive_phi, int number_fun, int N )
{
    double norm = EPS;
    
    //заполняем массивы
    if(make_points(N, massive_dots) != 0)
    {
        std::cout << "ERROR IN make_points.cpp" << std::endl;
        return -1;
    }

    // заполняем u
    for(int i = 0; i < N + 1; i++)
    {
        massive_u[i] = u(number_fun, massive_dots[i]);
    }
            
    // ищем коэфиценты в ряде
    make_coef(massive_ck, massive_u, massive_phi, N);

    double tmp = search_norma(massive_ck, number_fun, N);
    if (tmp > EPS)
        norm = tmp;

    return norm;
}
