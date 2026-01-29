#include "approximation.h"
#include "Pn.h"
#include "Ln.h"

void write_result(double *nodes2, int N, double *meanings1, double *meanings2, int number_fun, FILE *fout, int flag_L, int flag_P);

int main(int argc, char *argv[]) 
{
    int N; //число узлов
    int t; //тип узлов: 0 - равноудаленные, 1 - чебышевские, 2 - случайные
    int number_fun; // номер тестовой функции
    //int number_test = 1; // количество тестов для определения порядка сходимости
    double a, b; // левая и правая граница отрезка
    FILE *fout = nullptr;
    int flag = 1; // 1 - печатать таблицу разультатов в консоль; 0 - не печатать
    const char *filename_out = nullptr;

    double *mem, *nodes, *meanings, *nodes2, *meanings1, *meanings2;
    double *M, *coef;
    int *memory;
    int flag_L = 0, flag_P = 0;

    double error_L, error_P;

    if (argc == 7) 
    {
        if (toInt(argv[1], &N) != 0 || N < 2)
        {
            std::cerr << "Wrong parameter 'N'" << std::endl;
            return -1;
        }

        if (toInt(argv[2], &number_fun) != 0 || number_fun < 1 || number_fun > 5 )
        {
            std::cerr << "Wrong parameter 'number_fun'" << std::endl;
            return -1;
        }

        if (toInt(argv[3], &t) != 0 || (t != 0 && t != 1 && t != 0 && t != 2) )
        {
            std::cerr << "Wrong parameter 't'. Must be 0 - equidistant, 1 - Chebyshev, 2 - random" << std::endl;
            return -1;
        }

        if (toDouble(argv[4], &a) != 0)
        {
            std::cerr << "Wrong parameter 'a'" << std::endl;
            return -1;
        }

        if (toDouble(argv[5], &b) != 0 || a >= b )
        {
            std::cerr << "Wrong parameters 'a' and 'b'. Must be a < b" << std::endl;
            return -1;
        }

        filename_out = argv[6];

        fout = fopen(filename_out, "w");

        if (!fout)
        {
            std::cerr << "Can not open file " << filename_out << std::endl;
            return -1;
        }

        try
        {
            mem = new double[N * N + 3 * (2 * N - 1) + 3 * N];
            memory = new int[N]; // доп. память для метода Гаусса
            if (mem == nullptr || memory == nullptr)
            {
                std::cerr << "Can't allocate memory" << std::endl;
                return -1;
            }

            nodes = mem; // size = N
            meanings = nodes + N; // size = N

            coef = meanings + N; //искомые коэффициенты многочлена // size = N
            M = coef + N; // матрица для метода Гаусса // size = N * N

            nodes2 = M + N * N; // size = 2 * N - 1
            meanings1 = nodes2 + 2 * N - 1; // size = 2 * N - 1   
            meanings2 = meanings1 + 2 * N - 1; // size = 2 * N - 1
        }
        catch (std::bad_alloc &)
        {
            std::cerr << "Memory allocation error"<<std::endl;
            return -2;
        }

        catch(...)
        {
            std::cerr << "Unknown error..." << std::endl;
            return -2;
        }
        try
        {
            int res = generate_nodes(t, a, b, N, number_fun, nodes, meanings);
            if(res != 0)
            {
                std::cerr << "Something bad happend while generate nodes" << std::endl;
                return -1;
            }

            create_nodes2(nodes2, nodes, N);
            Ln_create(nodes, meanings, N, nodes2, meanings1);
            std::cout << "Polynom L_N built:" << std::endl;
        }
        catch (const char *error_message)
        {
            flag_L = 1;
            std::cout << error_message << std::endl;
        }
        catch(...)
        {
            flag_L = 1;
            std::cerr << "Unknown error..." << std::endl;
            return -2;
        }
        try
        {
            Pn_create(nodes, N, M, meanings, coef, memory);
            std::cout << "Polynom P_(N-1) built:" << std::endl;
            if(N < 20)
            {
                for(int i = 0; i < N; i++)
                {
                    std::cout << "coef_" << i << " = " << coef[i] << std::endl;
                }
            }

            Pn_calculate(coef, N, nodes2, meanings2);
        }
        catch (const char *error_message)
        {
            flag_P = 1;
            std::cout << error_message << std::endl;
        }
        catch(...)
        {
            flag_L = 1;
            std::cerr << "Unknown error..." << std::endl;
            return -2;
        }

        if(!flag_L)
            error_L = Ln_error(nodes2, meanings1, N, number_fun);
        else
            error_L = -1;
        if(!flag_P)
            error_P = Pn_error(nodes2, meanings2, N, number_fun);
        else
            error_P = -1;

        if (flag)
        {
            std::cout << "N = " << N << " number_fun = " << number_fun << " t = " << t << " a = " << a << " b = " << b << std::endl << std::endl;
            std::cout << "error_L = " << error_L << std::endl;
            std::cout << "error_P = " << error_P << std::endl;
        }
        write_result(nodes2, N, meanings1, meanings2, number_fun, fout, flag_L, flag_P);
        fclose(fout);

        delete[] mem;
        delete[] memory;
    }
    else 
    {
        fprintf(stderr, "Wrong extra parameters. Must be 'N number_fun t a b filename'\n");
        return -1;
    }
    return 0;

}

void write_result(double *nodes2, int N, double *meanings1, double *meanings2, int number_fun, FILE *fout, int flag_L, int flag_P)
{
    if(flag_L)
    {
        for(int i = 0; i < 2 * N - 1; i++)
            meanings1[i] = 0.;
    }
    if(flag_P)
    {
        for(int i = 0; i < 2 * N - 1; i++)
            meanings2[i] = 0.;
    }
    for (int i = 0; i < 2 * N - 1; i++)
    {
        double xi = nodes2[i];
        fprintf(fout, "%20.15lf %20.15lf %20.15lf %20.15lf \n", xi, meanings1[i], meanings2[i], fun(number_fun, xi));
    }
}
