#include "Pn.h"
#define e(i, j, n) ((i-1)*(n) + (j-1))

int solve(int n, double *M, double *b, double *x, int *memory)
{
    for (int j = 0; j < n; j++)
    {
        memory[j] = j;
    }

    double norm = 0.;
    for(int i = 0; i < n*n; ++i) 
    {
        if(M[i] > 0)
        {
            norm += M[i]; 
        }
        else 
        {
            norm -= M[i];
        }
    }
    double eps = norm * EPS / n*n;

    for (int step = 1; step < n + 1; step++)
    {
        int indMax = step;
        double max = M[e(step, step, n)];
        //ищем главный элемент
        for (int i = indMax + 1; i < n + 1; ++i)
        {
            if(fabs(M[e(step, i, n)]) > fabs(max))

            {
                indMax = i;
                max = M[e(step, i, n)];
            }
        }

        if ((max < eps && max > 0) || (max > -eps && !(max > 0)))
        if (max < eps)
        {
            return -1;
        }

        //меняем столбцы местами, если нужно
        if (indMax != step)
        {
            for (int i = 1; i < n + 1; ++i)
            {
                double tmp = M[e(i, step, n)];
                M[e(i, step, n)] = M[e(i, indMax, n)];
                M[e(i, indMax, n)] = tmp;
            }
            int tmp = memory[indMax - 1];
            memory[indMax - 1] = memory[step - 1];
            memory[step - 1] = tmp;
        }

        //шаг прямого хода метода гаусса
        for (int i = step + 1; i < n + 1; ++i)
        {
            double v = (M[e(i, step, n)] / max);
            for (int j = step; j < n + 1; ++j)
            {
                M[e(i, j, n)] -= v * M[e(step, j, n)];
            }
            b[i - 1] -= v * b[step - 1];
        }
    }

    //обратный ход метода гаусса
    for (int step = 1; step < n + 1; ++step)
    {
        for (int i = 1; i < n - step + 1; ++i)
        {
            b[i - 1] -= b[n - step] * M[e(i, n - step + 1, n)] / M[e(n - step + 1, n - step + 1, n)];
            M[e(i, n - step + 1, n)] = 0;
        }
        b[n - step] /= M[e(n - step + 1, n - step + 1, n)];
        M[e(n - step + 1, n - step + 1, n)] = 1;
    }

    for (int u = 0; u < n; ++u)
    {
        x[memory[u]] = b[u];
    }
    return 0;
}
