#include "fourier.h"
#include "functions.h"
#include "matrix.h"
#include<iomanip>

int main(int argc, char *argv[]) 
{
    int N; //число узлов
    int number_fun; // номер тестовой функции
    double p;

    double *memory = nullptr, *A, *b, *x;
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
            if (toInt(argv[3], &number_fun) != 0 || number_fun < 0 || number_fun > 6)
            {
                std::cerr << "Wrong parameter 'number_fun'" << std::endl;
                return -1;
            }
        }

        try
        {
            memory = new double[(N - 1) * (N - 1) + 2 * (N + 1)];

            if (memory == nullptr)
            {
                std::cerr << "Can't allocate memory" << std::endl;
                return -1;
            }

            A = memory;
            b = A + (N - 1) * (N - 1);
            x = b + (N + 1);
            //mem = x + (N + 1);

            make_fourier_matrix(A, N, p); //делает матрицу размера (N - 1) * (N - 1)
            //std::cout << "Matrix A = " << std::endl;
            //print_matrix(A, N - 1, 10); // последний аргумент - макс размер печатаемых элементов
            
            if(argc == 3)
            {
                make_b_from_A(A, N - 1, b + 1); //делает вектор размера (N - 1)
                b[0] = 0;
                b[N] = b[N - 1];
            }
            else if(number_fun == 0)
            {
                for(int i = 0; i < N + 1; i++)
                {
                    x[i] = i + 1;
                }
                x[N] = x [N - 1];
                x[0] = 0.;
                make_b_from_x(A, x + 1, N - 1, b + 1);
                b[0] = 0;
                b[N] = b[N - 1];
            }
            else
            {
                make_b_from_f(b + 1, N - 1, number_fun); //делает вектор размера (N - 1)
                b[0] = 0;
                b[N] = b[N - 1];

            }

            //std::cout << "b = ";
            //print_vector(b, N + 1, 10); // последний аргумент - макс размер печатаемых элементов

            method_fourier(x, N, p, b);
            std::cout << "Answer: ";
            print_vector(x, N + 1, 10); // последний аргумент - макс размер печатаемых элементов

            //mult_matrix_vector(A, x + 1, mem, N - 1);
            //std::cout << "Vector Ax =  ";
            //print_vector(mem, N - 1, 10);

            std::cout << "||Ax - b|| = " << std::uppercase <<  std::scientific << residual(A, b + 1, x + 1, N - 1) << std::endl;
            
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
        "f1(x)=x^2 - 2x                          	    \n"
        "f2(x)=x^3 - 3x                                 \n"
        "f3(x)=sin(PI*x/2)               	            \n"
        "f4(x)=1/(1.+25.*(x-1)^2) - 1/26                \n"
        "f5(x)=1 ? x < 0.6 && x > 0.4: 0;               \n"
        "f6(x)=your_test / 0                            \n";
    fprintf(stderr, "Input: %s N p (number_fun) \n%s\n", str, txt);
}
