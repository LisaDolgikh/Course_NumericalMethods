#include "fourier.h"
#include "functions.h"
#include "matrix.h"
#include<iomanip>

int main(int argc, char *argv[]) 
{
    int N; //число узлов
    int number_fun; // номер тестовой функции
    double p;

    double *memory = nullptr, *b, *x;
    //double *mem;

    if (argc == 3 || argc == 4) 
    {
        if (toInt(argv[1], &N) != 0 || N < 3)
        {
            std::cerr << "Wrong parameter 'N'" << std::endl;
            return -1;
        }

        if (toDouble(argv[2], &p) != 0)
        {
            std::cerr << "Wrong parameter 'p'" << std::endl;
            return -1;
        }
        if(argc == 4)
        {
            if (toInt(argv[3], &number_fun) != 0 || number_fun < 0 || number_fun > 5)
            {
                std::cerr << "Wrong parameter 'number_fun'" << std::endl;
                return -1;
            }
        }

        try
        {
            memory = new double[ 2 * (N + 1)];

            if (memory == nullptr)
            {
                std::cerr << "Can't allocate memory" << std::endl;
                return -1;
            }

            b = memory;
            x = b + (N + 1);
            //make_fourier_matrix(A, N, p); //делает матрицу размера (N - 1) * (N - 1)
            
            if(argc == 3)
            {
                for(int i = 0; i < N + 1; i++)
                {
                    x[i] = i;
                }
                x[N] = x [N - 1];
                x[0] = 0.;
                make_b_from_x(p, x + 1, N, b + 1);
                b[0] = 0;
                b[N] = b[N - 1];
            }
            else
            {
                make_b_from_f(b + 1, N, number_fun); //делает вектор размера (N - 1)
                b[0] = 1;
                b[N] = 1;
                //b[0] = 0;
                //b[N] = b[N - 1];

            }

            method_fourier(x, N, p, b);
            std::cout << "Answer: ";
            print_vector(x, N + 1, 10); // последний аргумент - макс размер печатаемых элементов

            double h = 1. / ((double)N - 0.5);

            FILE *fout = nullptr;
            const char *filename_out = "out.txt";

            fout = fopen(filename_out, "w");
            if (!fout)
            {
                std::cerr << "Can not open file " << filename_out << std::endl;
                return -1;
            }
            for(int i = 0; i <= N; i++)
            {
                double c = - 1. / (1 + exp(1.) * exp(1.));
                double y = 0.;
                y = c * exp(i*h) + c * exp(1.) * exp(1.) * exp(-i*h) + 1;
                fprintf(fout, "%20.15lf %20.15lf \n", x[i], fabs(x[i] -y));
                //fprintf(fout, "%20.15lf %20.15lf \n", x[i], fabs(x[i] + i*h*(i*h - 2.)/2.) );
            }
            fclose(fout);
            
        }
        catch (std::bad_alloc &)
        {
            std::cerr << "Memory allocation error"<<std::endl;
            return -2;
        }

        catch(...)
        {
            std::cerr << "Unknown error..." << std::endl;
            delete[] memory;
            return -2;
        }
        delete[] memory;
    }
    else 
    {
        fprintf(stderr, "Wrong extra parameters. Must be: N p (number_fun)\n");
        manual(argv[0]);
        return -1;
    }
    return 0;

}

void manual (const char *str)
{
    const char *txt = 
        "Functions:                                     \n"
        "f1(x)=1                                  	    \n"
        "f1(x)=x^2 - 2x                          	    \n"
        "f2(x)=x^3 - 3x                                 \n"
        "f3(x)=sin(PI*x/2)               	            \n"
        "f4(x)=1/(1.+25.*(x-1)^2) - 1/26                \n"
        "f5(x)=your_test / 0                            \n";
    fprintf(stderr, "Input: %s N p (number_fun) \n%s\n", str, txt);
}
