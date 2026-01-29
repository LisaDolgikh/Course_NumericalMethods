#include "richardson.h"
#include "fourier.h"
#include "functions.h"
#include "matrix.h"

int main(int argc, char *argv[]) 
{
    int N, number_test, number_fun;
    double p, eigenvalue_m, eigenvalue_M, tau, q0, q = 1.;
    double resid, resid_0;
    FILE *fout = nullptr;
    const char *filename_out = nullptr;

    double *memory = nullptr, *A, *b, *x, *trash;

    
    if (argc == 5 || argc == 6) 
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
        
        if (toInt(argv[3], &number_test) != 0)
        {
            std::cerr << "Wrong parameter 'number_test'" << std::endl;
            return -1;
        }

        filename_out = argv[4];

        fout = fopen(filename_out, "w");
        if (!fout)
        {
            std::cerr << "Can not open file " << filename_out << std::endl;
            return -1;
        }

        if(argc == 6)
        {
            if (toInt(argv[5], &number_fun) != 0 || number_fun < 0 || number_fun > 6)
            {
                std::cerr << "Wrong parameter 'number_fun'" << std::endl;
                return -1;
            }

        }

        try
        {
            memory = new double[N * N + 3 * N];

            if (memory == nullptr)
            {
                std::cerr << "Can't allocate memory" << std::endl;
                return -1;
            }

            A = memory;
            b = A + N * N;
            x = b + N;
            trash = x + N;
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
        
        make_fourier_matrix(A, N + 1, p); // получаем матрицу N * N
        //std::cout << "Matrix A = " << std::endl;
        //print_matrix(A, N, 10); // последний аргумент - макс размер печатаемых элементов
            
        if(argc == 5)
        {
            make_b_from_A(A, N, b);
        }
        else if(number_fun == 0)
        {
            for(int i = 0; i < N; i++)
            {
                x[i] = i;
            }
            x[0] = 0.;
            make_b_from_x(A, x, N, b);
        }
        else
        {
            make_b_from_f(b, N, number_fun);
        }

        //std::cout << "b = ";
        //print_vector(b, N, 10); // последний аргумент - макс размер печатаемых элементов

        eigenvalue_m = lambda_m(1, N + 1, p);
        eigenvalue_M = lambda_m(N, N + 1, p);
        tau = 2. / (eigenvalue_m + eigenvalue_M);

        q0 = (eigenvalue_M - eigenvalue_m) / (eigenvalue_M + eigenvalue_m);
        std::cout << "q0 = " << q0 << std::endl;

        resid_0 = method_richardson(x, A, b, tau, N, 0, trash);

        for(int iter = 0; iter <= number_test; iter++)
        {
            resid = method_richardson(x, A, b, tau, N, iter, trash);
            fprintf(fout, "%d %20.15lf %20.15lf \n", iter, resid, resid_0 * q);
            q *= q0;
        }

        std::cout << "||Ax^mIter - b|| = " << std::fixed << std::setprecision(15) << residual(A, b, x, N) << std::endl;
        std::cout << "Answer: ";
        print_vector(x, N, 10); // последний аргумент - макс размер печатаемых элементов
        delete[] memory;
    }
    else 
    {
        fprintf(stderr, "Wrong extra parameters. Must be: N p number_test filename_out (number_fun)\n");
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
    fprintf(stderr, "Input: %s  N p number_test filename_out (number_fun)\n%s\n", str, txt);
}
