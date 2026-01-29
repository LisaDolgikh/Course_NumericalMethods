#include "bsolver.h"
#include "fourier.h"
#include "functions.h"
#include "matrix.h"

int main(int argc, char *argv[]) 
{
    int N, number_test, number_fun;
    double p = 0., tau = 0.1, q0, q = 1.;
    double resid, resid_0;
    FILE *fout = nullptr;
    const char *filename_out = nullptr;

    double *memory = nullptr, *A, *B, *b, *x, *trash, *trash1;

    
    if(argc == 5 || argc == 6) 
    {
        if(toInt(argv[1], &N) != 0 || N < 3)
        {
            std::cerr << "Wrong parameter 'N'" << std::endl;
            return -1;
        }

        if(toDouble(argv[2], &p) != 0)
        {
            std::cerr << "Wrong parameter 'p'" << std::endl;
            return -1;
        }

        if(toInt(argv[3], &number_test) != 0)
        {
            std::cerr << "Wrong parameter 'number_test'" << std::endl;
            return -1;
        }

        filename_out = argv[4];

        fout = fopen(filename_out, "w");
        if(!fout)
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
            memory = new double[2 * (N - 1) * (N - 1) + 4 * (N + 1)];

            if (memory == nullptr)
            {
                std::cerr << "Can't allocate memory" << std::endl;
                return -1;
            }

            A = memory;
            B = A + (N - 1) * (N - 1);
            b = B + (N - 1) * (N - 1);
            x = b + (N + 1);
            trash = x + (N + 1);
            trash1 = trash + (N + 1);
        }
        catch(std::bad_alloc &)
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

        make_matrix_3(A, N - 1, p); 
        make_fourier_matrix(B, N, p); //делает матрицу размера (N - 1) * (N - 1)
        
        std::cout << "Matrix A = " << std::endl;
        //print_matrix(A, N - 1, 10); // последний аргумент - макс размер печатаемых элементов

        std::cout << "Matrix B = " << std::endl;
        //print_matrix(B, N - 1, 10); // последний аргумент - макс размер печатаемых элементов
        
        reverse_fourier_matrix_without_0(p, B, N, trash, trash1);

        std::cout << "Matrix B^-1 = " << std::endl;
        //print_matrix(B, N - 1, 10); // последний аргумент - макс размер печатаемых элементов
            
        if(argc == 5)
        {
            make_b_from_A(A, N - 1, b + 1); //делает вектор размера (N - 1)
            b[0] = 0;
            b[N] = b[N - 1];
        }
        else if(number_fun == 0)
        {
            for(int i = 0; i < N + 1; i++)
            {
                x[i] = i;
            }
            x[0] = 0.;
            make_b_from_x(A, x + 1, N - 1, b + 1);
			b[0] = 0;
			b[N] = b[N -1 ];
        }
        else
        {
            make_b_from_f(b + 1, N - 1, number_fun); //делает вектор размера (N - 1)
            b[0] = 0;
            b[N] = b[N - 1];
        }
        //std::cout << "b = ";
        //print_vector(b, N + 1, 10); // последний аргумент - макс размер печатаемых элементов

        //ищем теоретическую скорость сходимости
        q0 = find_q0(A, (N - 1));
        std::cout << "q0 = " << q0 << std::endl;
        resid_0 = method_BSolver(x + 1, A, B, b + 1, tau, N - 1, 0, trash, trash1);
		std::cout << "Метод 0 запущен" << std::endl;

        for (int iter = 0; iter < number_test + 1; iter++)
        {
            resid = method_BSolver(x + 1, A, B, b + 1, tau, N - 1, iter, trash, trash1);
			std::cout << "Метод для максимума интераций" << iter << "запущен" << std::endl;
            fprintf(fout, "%d %20.15lf %20.15lf \n", iter, resid, q * resid_0);
            q *= q0;
        }

        x[0] = 0.;
        x[N] = x[N - 1];
        std::cout << "Solution = ";
        print_vector(x, N + 1, 10); // последний аргумент - макс размер печатаемых элементов
        std::cout << "||Ax^mIter - b|| = " << std::uppercase << std::scientific  << resid << std::endl;

        fclose(fout);
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
