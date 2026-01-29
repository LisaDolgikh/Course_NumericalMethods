#include "Pm.h"

void Pm_create(double *nodes, int N, double *M, double *meanings, double *coef, int *memory)
{
	for(int i = 1; i < N + 1; i++)
	{
		double tmp = 1.;
		if(i % 2 == 0)
		{
			M[e(i, N, N)] = -1.;
		}
		else
		{
			M[e(i, N, N)] = 1.;
		}

		for(int j = 1; j < N; j++) 
		{
			M[e(i, j, N)] = tmp;
			tmp *= nodes[i - 1];
            if(fabs(tmp) < 1e-200)
            {
                tmp = 0.;
            }
		}
		tmp = 1.;
	}

	if(solve(N, M, meanings, coef, memory) != 0) 
	{
		std::cerr << "Something bad happend while solving system" << std::endl;
		for(int i = 0; i < N; ++i)
		{
			coef[i] = 0.;
		}
		throw "Bad nodes";
	}
}

void Pm_calculate(double *coef, int N, int m, double *nodes2, double *meanings2)
{
	for(int i = 0; i < 2 * N - 1; i++)
	{
		meanings2[i] = Pm_calculate_x(coef, m, nodes2[i]);
	}
}

double Pm_calculate_x(double *coef, int m, double x)
{
	double res = 0.;
	double tmp = 1.;
	for (int i = 0; i <= m; i++)
    {
		res += coef[i] * tmp;
		tmp *= x;
        if(fabs(tmp) < 1e-200)
        {
            tmp = 0.;
        }
    }
	return res;
}

double Pm_error(double *nodes2, double *meanings2, int N, int number_fun)
{
	double max = 0.;
	for(int i = 0; i < 2 * N - 1; i++)
	{
		if(fabs(meanings2[i] - fun(number_fun, nodes2[i])) > max)
		{
			max = fabs(meanings2[i] - fun(number_fun, nodes2[i]));
		}
	}
	return max;
}

