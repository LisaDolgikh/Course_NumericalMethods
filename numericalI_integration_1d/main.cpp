#include "functions.h"
#include "integration.h"

void manual (const char *str);

int main(int argc, char *argv[]) 
{
    double a, b; // левая и правая граница отрезка
    int number_fun;
    int flag = 1; // 1 - печатать разультаты в консоль; 0 - не печатать

    double integ;
    fun_t f, functions[] = {fun0, fun1, fun2, fun3, fun4, fun5, fun6, fun7, fun8, fun9};
    

    if (argc == 4 || argc == 6) 
    {
        if (toDouble(argv[1], &a) != 0)
        {
            std::cerr << "Wrong parameter 'a'" << std::endl;
            return -1;
        }

        if (toDouble(argv[2], &b) != 0 || a >= b )
        {
            std::cerr << "Wrong parameters 'a' and 'b'. Must be a < b" << std::endl;
            return -1;
        }

        if (toInt(argv[3], &number_fun) != 0 || number_fun < 0 || number_fun > 9)
        {
            std::cerr << "Wrong parameter 'number_fun'" << std::endl;
            return -1;
        }
        f = functions[number_fun];

        //вычисляем точное значение интеграла
        if(number_fun < 4)
        {
            integ = pow(b, (number_fun + 1)) - pow(a, (number_fun + 1));
        }

        else if(number_fun == 4)
        {
            integ = exp(b) - exp(a);
        }

        else if(number_fun == 5)
        {
            integ = exp(b) * (b - 1) - exp(a) * (a - 1);
        }

        else if(number_fun == 6)
        {
            integ = (sin(100*a) - sin(100*b)) / 100.;
        }

        else if(number_fun == 7)
        {
            integ = (exp(a) - exp(b)) / 1000.;
        }

        else if(number_fun == 8)
        {
            integ = 2 * (sqrt(b) - sqrt(a));
        }

        else //if(number_fun == 9)
        {
            integ = PI;
        }

        if(flag)
        {
            std::cout << "a = " << a << " b = " << b << " number_fun = " << number_fun << std::endl << std::endl;
            std::cout << "Rectangle_method(f) = " << std::fixed << rectangle_method(a, b, f) << std::endl;
            std::cout << "Sympson_method(f) = " << std::fixed << simpson_method(a, b, f) << std::endl;
            std::cout << "Gauss_method(f) = " << std::fixed << gauss_method(a, b, f) << std::endl;
            std::cout << "Integral(f) = " << std::fixed << integ << std::endl << std::endl;
        }

        if (argc == 6)
        {
            int N;
            int number_test = 10; //количество тестов для определения p
            FILE *fout = nullptr;
            const char *filename_out = nullptr;
            double R, S, G, error_R, error_S, error_G; //метод прямоуг, Симсона, Гаусса, погрешности

            if (toInt(argv[4], &N) != 0 || N < 2)
            {
                std::cerr << "Wrong parameter 'N'" << std::endl;
                return -1;
            }

            filename_out = argv[5];
            fout = fopen(filename_out, "w");
            if (!fout)
            {
                std::cerr << "Can not open file " << filename_out << std::endl;
                return -1;
            }

            for(int k = 0; k < number_test; k++)
            {
                R = composite_rectangle_method(a, b, f, N);
                S = composite_simpson_method(a, b, f, N);
                G = composite_gauss_method(a, b, f, N);

                if(k == 0)
                {
                    std::cout << "a = " << a << " b = " << b << " number_fun = " << number_fun << " N = " << N << std::endl << std::endl;
                    std::cout << "Composite_rectangle_method(f) = " << std::fixed << R << std::endl;
                    std::cout << "Composite_sympson_method(f) = " << std::fixed << S << std::endl;
                    std::cout << "Composite_gauss_method(f) = " << std::fixed << G << std::endl;
                    std::cout << "Integral(f) = " << std::fixed << integ << std::endl << std::endl;
                }

                error_R = log(fabs(R - integ));
                error_S = log(fabs(S - integ));
                error_G = log(fabs(G - integ));
                fprintf(fout, "%e %e %e %e \n",log((double)(N)), error_R, error_S, error_G);
                N = N * 2;
            }
            fclose(fout);
        }

    }
    else 
    {
        fprintf(stderr, "Wrong extra parameters. Must be 'a b number_fun (N filename)'\n");
        manual(argv[0]);
        return -1;
    }
    return 0;
}

void manual (const char *str)
{
    const char *txt = 
        "Functions:                                           \n"
        "f0(x) = 1                                            \n"
        "f1(x) = 2 x                                          \n"
        "f2(x) = 3 x^2                                        \n"
        "f3(x) = 4 x^3                                        \n"
        "f4(x) = exp(x)                                       \n"
        "f5(x)= x * exp(x)                                    \n"
        "f6(x)= cos(100 x)                 I[0, PI] = 0       \n"
        "f7(x) = exp(-1000 * x)            I[0,1] = 10^(-3)   \n"
        "f8(x)= 1 / sqrt(x)                                   \n"
        "f9(x)= 1 / sqrt(1 - x * x)        I[-1, 1] = PI      \n";
    fprintf(stderr, "Input: %s a b number_fun (N filename_out)\n%s\n", str, txt);
}

