#include "fourier.h"

int toInt(const char *str, int *value);


double u(int number_fun, double x)
{
    switch(number_fun)
    {
        case 1:
            return x*x - 2*x;

        case 2:
            return x*x*x-3.*x;
            break;

        case 3:
            return sin(PI*x/2);

        case 4:
            return 1/(double)(1.+25.*(x-1)*(x-1)) - 1./26.;

        case 5:
            return x < 0.6 && x > 0.4 ? 1: 0;

        case 6:
            return 0;

        default:
            return 0;

    }
}

int main(int argc, char *argv[]) 
{
    int N; //число узлов
    int number_fun; // номер тестовой функции

    FILE *fout = nullptr;
    const char *filename = nullptr;

    double *mem;
    double *massive_ck;
    double *massive_phi;
    double *massive_u;
    double *massive_dots;

    if (argc == 4) 
    {
        if (toInt(argv[1], &N) != 0 || N < 3)
        {
            std::cerr << "Wrong parameter 'N'" << std::endl;
            return -1;
        }

        if (toInt(argv[2], &number_fun) != 0 || number_fun < 1 || number_fun > 6)
        {
            std::cerr << "Wrong parameter 'number_fun'" << std::endl;
            return -1;
        }

        filename = argv[3];

        fout = fopen(filename, "w");

        if (!fout)
        {
            std::cerr << "Can not open file " << filename << std::endl;
            return -1;
        }

        try
        {
            mem = new double[(N+1) * 4] ;

            if (mem == nullptr)
            {
                std::cerr << "Can't allocate memory" << std::endl;
                return -1;
            }
            massive_ck = mem;
            massive_phi = massive_ck + N+1;
            massive_u = massive_phi + N+1;
            massive_dots = massive_u + N+1;
            
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

        //заполняем массивы
        if(make_points(N, massive_dots) != 0)
        {
            std::cout << "ERROR IN make_points.cpp" << std::endl;
            delete [] mem;
            return -3;
        }

        // заполняем u
        for(int i = 0; i < N + 1; i++)
        {
            massive_u[i] = u(number_fun, massive_dots[i]);
        }
        
        // ищем коэфиценты в ряде
        make_coef(massive_ck, massive_u, massive_phi, N);
        
        /*double norm = search_norma(massive_ck, number_fun, N);
        std::cout << norm << std::endl; */


        // _________________________________________________
        // запись в файл

        double xk, xk1, xk2;
        for(int k = 0; k < N; k++)
        {
            xk = massive_dots[k];
            xk1 = 2 * xk / 3. + massive_dots[k+1] / 3.;
            xk2 = xk / 3. + 2 * massive_dots[k+1] / 3.;
            fprintf(fout, "%20.15lf %20.15lf %20.15lf \n", xk, back_fourier(massive_ck, xk, N), u(number_fun, xk));
            fprintf(fout, "%20.15lf %20.15lf %20.15lf \n", xk1, back_fourier(massive_ck, xk1, N), u(number_fun, xk1));
            fprintf(fout, "%20.15lf %20.15lf %20.15lf \n", xk2, back_fourier(massive_ck, xk2, N), u(number_fun, xk2));
        };
        xk = massive_dots[N];
        fprintf(fout, "%20.15lf %20.15lf %20.15lf \n", xk, back_fourier(massive_ck, xk, N), u(number_fun, xk));

        fclose(fout);
        delete[] mem;
    }

    
    else if(argc == 5) 
    {
        int number_test; // количество тестов для определения порядка сходимости
        double *massive_lognorm;
        double *massive_logN;

        if (toInt(argv[1], &N) != 0 || N < 3)
        {
            std::cerr << "Wrong parameter 'N'" << std::endl;
            return -1;
        }

        if (toInt(argv[2], &number_fun) != 0 || number_fun < 1 || number_fun > 6)
        {
            std::cerr << "Wrong parameter 'number_fun'" << std::endl;
            return -1;
        }

        filename = argv[3];

        fout = fopen(filename, "w");

        if (!fout)
        {
            std::cerr << "Can not open file " << filename << std::endl;
            return -1;
        }

        if (toInt(argv[4], &number_test) != 0 || number_test < 2)
        {
            std::cerr << "Wrong parameter 'number_test'" << std::endl;
            return -1;
        }

        try
        {
            massive_lognorm = new double[number_test];
            massive_logN = new double[number_test] ;

            if (massive_lognorm == nullptr || massive_logN == nullptr)
            {
                std::cerr << "Can't allocate memory" << std::endl;
                return -1;
            }
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

        for(int j = 1; j <= number_test; j++ )
        {         
            try
            {
                mem = new double[(N+1) * 4 * j] ;

                if (mem == nullptr)
                {
                    std::cerr << "Can't allocate memory" << std::endl;
                    return -1;
                }
                massive_ck = mem;
                massive_phi = massive_ck + (N+1)*j;
                massive_u = massive_phi + (N+1)*j;
                massive_dots = massive_u + (N+1)*j;
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
            double error = error_fourier(massive_ck, massive_dots, massive_u, massive_phi, number_fun, (N + 1) * j - 1 );
            //std::cout << N * j << "      " << error << std::endl;
            massive_lognorm[j - 1] = log(1. / error);
            massive_logN[j - 1] = log(N * j);
	    delete[] mem;
        }
        // _________________________________________________
        // запись в файл
        for(int j = 0; j < number_test; j++)
        {
            fprintf(fout, "%20.15lf %20.15lf \n", massive_lognorm[j], massive_logN[j]);
        };

        fclose(fout);
        delete[] massive_logN;
        delete[] massive_lognorm;
    }
    else 
    {
        fprintf(stderr, "Wrong extra parameters. Must be:\n");
        manual(argv[0]);
        return -1;
    }
    return 0;

}

int toInt(const char *str, int *value) 
{
    long result;
    char *e;

    errno = 0;

    result = strtol(str, &e, 10);

    if (errno != 0 || *e != '\0') 
        return -1;

    if (INT_MIN <= result && result <= INT_MAX) 
    {
        *value = (int) result;
        return 0;
    }

    return -1;
}

void manual (const char *str)
{
    const char *txt = 
        "Functions:                                     \n"
        "f1(x)=x^2 - 2x                          	    \n"
        "f2(x)=x^3 - 3x                                 \n"
        "f3(x)=sin(PI*x/2)               	            \n"
        "f4(x)=1/(1.+25.*(x-1)^2) - 1/26                \n"
        "f5(x)=1 ? x < 0.6 && x > 0.4: 0;               \n"
        "f6(x)=your_test / 0                            \n";
    fprintf(stderr, "Input: %s N number_fun filename\n%s\n", str, txt);
}
