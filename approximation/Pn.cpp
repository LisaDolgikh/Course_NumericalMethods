#include "Pn.h"

void Pn_create(double *nodes, int N, double *M, double *meanings, double *coef, int *memory)
{
	for(int i = 1; i < N + 1; i++)
	{
		double m = 1.;
		for(int j = 1; j < N + 1; j++) 
		{
			M[e(i, j, N)] = m;
			m *= nodes[i - 1];
                        if(fabs(m) < 1e-200)
                        {
                            m = 0.;
                        }
		}
		m = 1.;
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

void Pn_calculate(double *coef, int N, double *nodes2, double *meanings2)
{
	for(int i = 0; i < 2 * N - 1; i++)
	{
		meanings2[i] = Pn_calculate_x(coef, N, nodes2[i]);
	}
}

double Pn_calculate_x(double *coef, int N, double x)
{
	double res = 0.;
	double tmp = 1.;
	for (int i = 0; i < N; i++)
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

double Pn_error(double *nodes2, double *meanings2, int N, int number_fun)
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
