#include "Ln.h"
#include "approximation.h"

double Ln_Phi(double *nodes, int N, double x, int i)
{
    double res = 1.;

    for (int j = 0; j < N; j++)
    {
		if(j != i) 
        {
            if(fabs(nodes[i] - nodes[j]) < EPS) 
            {
                std::cerr << "fabs( "<< nodes[i] << " - " << nodes[j] << " ) < " << EPS << std::endl;
                throw "Bad nodes";
            }
            else res *= (x - nodes[j]) / (nodes[i] - nodes[j]);
        }
    }
	return res;
}

void Ln_create(double *nodes, double *meanings, int N, double *nodes2, double *meanings2)
{
	double res = 0., x = 0.;
	
	for(int m = 0; m < 2 * N - 1; m++)
	{
		res = 0.;
		x = nodes2[m];
		for (int i = 0; i < N; i++)
		{
			res += meanings[i] * Ln_Phi(nodes, N, x, i);
		}
		meanings2[m] = res;
	}
}

double Ln_error(double *nodes2, double *meanings1, int N, int number_fun)
{
	double max = 0.;
	for(int i = 0; i < 2 * N - 1; i++)
	{
		if(fabs(meanings1[i] - fun(number_fun, nodes2[i])) > max)
		{
			max = fabs(meanings1[i] - fun(number_fun, nodes2[i]));
		}
	}
	return max;
}
