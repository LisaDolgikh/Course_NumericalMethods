#include "interpolation.h"
#include "Pm.h"

void write_result(double *nodes2, int N, double *meanings2, int number_fun, FILE *fout, int flag_P);

int main(int argc, char *argv[]) 
{
    int N; //число узлов
    int m; //степень искомого полинома
    int number_fun; // номер тестовой функции
    int t; //тип узлов: 0 - равноудаленные, 1 - чебышевские, 2 - случайные
    double a, b; // левая и правая граница отрезка
    FILE *fout = nullptr, *fres = nullptr;
    int flag = 1; // 1 - печатать таблицу разультатов в консоль; 0 - не печатать
    const char *filename_out = nullptr;
    //const char *filename_res = nullptr; 
    //по умолчанию filename_res = res.txt

    double *mem, *nodes, *new_nodes, *meanings, *new_meanings, *nodes2, *meanings2;
    double *M, *coef, *right_part;
    int *memory;
    int flag_P = 0;
    int counter = 1;
    double error_P;

    if (argc == 8) 
    {
        if (toInt(argv[1], &N) != 0 || N < 2)
        {
            std::cerr << "Wrong parameter 'N'" << std::endl;
            return -1;
        }

        if (toInt(argv[2], &m) != 0 || m < 1 || m > N - 2)
        {
            std::cerr << "Wrong parameter 'm'" << std::endl;
            return -1;
        }

        int k = m + 2;

        if (toInt(argv[3], &number_fun) != 0 || number_fun < 1 || number_fun > 5 )
        {
            std::cerr << "Wrong parameter 'number_fun'" << std::endl;
            return -1;
        }

        if (toInt(argv[4], &t) != 0 || (t != 0 && t != 1 && t != 2) )
        {
            std::cerr << "Wrong parameter 't'. Must be 0 - equidistant, 1 - Chebyshev, 2 - random" << std::endl;
            return -1;
        }

        if (toDouble(argv[5], &a) != 0)
        {
            std::cerr << "Wrong parameter 'a'" << std::endl;
            return -1;
        }

        if (toDouble(argv[6], &b) != 0 || a >= b )
        {
            std::cerr << "Wrong parameters 'a' and 'b'. Must be a < b" << std::endl;
            return -1;
        }

        filename_out = argv[7];

        fout = fopen(filename_out, "w");

        if (!fout)
        {
            std::cerr << "Can not open file " << filename_out << std::endl;
            return -1;
        }

        try
        {
            // k = m + 2
            mem = new double[ k * k + 4 * k + 2 * N + 2 * (2 * N - 1)];
            memory = new int[k]; // доп. память для метода Гаусса
            if (mem == nullptr || memory == nullptr)
            {
                std::cerr << "Can't allocate memory" << std::endl;
                return -1;
            }

            nodes = mem; // size = N
            meanings = nodes + N; // size = N

            new_nodes = meanings + N; // size = k 
            new_meanings = new_nodes + k; // size = k 

            coef = new_meanings + k; //искомые коэффициенты многочлена и h // size = k
            M = coef + k; // матрица для метода Гаусса // size = k * k
            right_part = M + k * k; // правая часть для Гаусса // size = k 

            nodes2 = right_part + k; // size = 2 * N - 1 
            meanings2 = nodes2 + 2 * N - 1; // size = 2 * N - 1
        }
        catch (std::bad_alloc &)
        {
            std::cerr << "Memory allocation error"<<std::endl;
            fclose(fout);
            return -2;
        }

        catch(...)
        {
            std::cerr << "Unknown error..." << std::endl;
            fclose(fout);
            return -2;
        }
        if(m == N - 2)
        {
            try
            {
                int res = generate_nodes(t, a, b, N, number_fun, nodes, meanings);
                if(res != 0)
                {
                    std::cerr << "Something bad happend while generate nodes" << std::endl;
                    return -1;
                }
                Pm_create(nodes, k, M, meanings, coef, memory);

                if(N < 10)
                {
                    std::cout << "Polynom P_m built:" << std::endl;
                    for(int i = 0; i <= m; i++)
                    {
                        std::cout << "coef_" << i << " = " << coef[i] << std::endl;
                    }
                }

                fres = fopen("res.txt", "w");

                if (!fres)
                {
                    std::cerr << "Can not open file 'res.txt'" << std::endl;
                    fclose(fout);
                    delete[] mem;
                    delete[] memory;
                    return -1;
                }

                fprintf(fres, " N = %d |  m = %d | counter = %d  | h = %20.15lf \n", N, m, counter, coef[k - 1] );
                for(int i = 0; i < k; i++)
                {
                    fprintf(fres, " new_nodes[ %d ] = %20.15lf  \n", i + 1, nodes[i] );
                }
                fclose(fres);

                create_nodes2(nodes2, nodes, N);
                Pm_calculate(coef, N, m, nodes2, meanings2);
            }
            catch (const char *error_message)
            {
                flag_P = 1;
                //delete[] mem;
                //delete[] memory;
                std::cerr << error_message << std::endl;
            }
            catch(...)
            {
                flag_P = 1;
                delete[] mem;
                delete[] memory;
                fclose(fout);
                std::cerr << "Unknown error..." << std::endl;
                return -2;
            }
            if(!flag_P)
                error_P = Pm_error(nodes2, meanings2, N, number_fun);
            else
                error_P = -1;

            if (flag)
            {
                std::cout << "N = " << N << " m = " << m << " number_fun = " << number_fun << " t = " << t << " a = " << a << " b = " << b << std::endl << std::endl;
                std::cout << "counter = " << counter << " h = " << coef[k - 1] << " error_P = " << error_P << std::endl;
            }
            write_result(nodes2, N, meanings2, number_fun, fout, flag_P);
            fclose(fout);

            delete[] mem;
            delete[] memory;
        }
        else if(m < N - 2)
        {
            try
            {
                // генерируем сетку из N узлов
                int res = generate_nodes(t, a, b, N, number_fun, nodes, meanings);
                if(res != 0)
                {
                    std::cerr << "Something bad happend while generate nodes" << std::endl;
                    return -1;
                }

                // генерируем первый вариант узлов
                create_new_nodes(new_nodes, nodes, new_meanings, meanings, k, N);
                /*for(int i = 0; i < k; i++)
                {
                    std::cout << " new_nodes[ " << i + 1 << "] = " <<  new_nodes[i] << std::endl;
                }*/
                
                for (int i = 0; i < k; i++)
                {
                    right_part[i] = new_meanings[i];
                }

                //запускаем создание многочлена и решение СЛУ
                Pm_create(new_nodes, k, M, right_part, coef, memory);

                fres = fopen("res.txt", "w");

                if (!fres)
                {
                    std::cerr << "Can not open file 'res.txt'" << std::endl;
                    fclose(fout);
                    delete[] mem;
                    delete[] memory;
                    return -1;
                }

                fprintf(fres, " N = %d |  m = %d | counter = %d | h = %20.15lf \n", N, m, counter, coef[k - 1] );
                for(int i = 0; i < k; i++)
                {
                    fprintf(fres, " new_nodes[ %d ] = %20.15lf  \n", i + 1, new_nodes[i] );
                }
                fprintf(fres, " \n");
                res = -1;

                while(res != 0 && counter < 1000)
                {
                    res = s_algorithm(nodes, new_nodes, coef, meanings, new_meanings, k, N);
                    if(res != 0)
                    {
                        counter += 1;
                        for (int i = 0; i < k; i++)
                        {
                            right_part[i] = new_meanings[i];
                        }

                        //запускаем создание многочлена и решение СЛУ
                        Pm_create(new_nodes, k, M, right_part, coef, memory);

                        
                        fprintf(fres, " N = %d |  m = %d | counter = %d  | h = %20.15lf \n", N, m, counter, coef[k - 1] );
                        
                        for(int i = 0; i < k; i++)
                        {
                            fprintf(fres, " new_nodes[ %d ] = %20.15lf  \n", i + 1, new_nodes[i] );
                        }
                        fprintf(fres, " \n");

                    }
                } 
                if(counter >= 1000)
                {
                    std::cerr << "The algorithm is looping (counter >= 1000)" << std::endl;
                    fclose(fout);
                    fclose(fres);
                    delete[] mem;
                    delete[] memory;
                    return -1;

                }
                fclose(fres);
                create_nodes2(nodes2, nodes, N);
                Pm_calculate(coef, N, m, nodes2, meanings2); 
            }
            catch (const char *error_message)
            {
                flag_P = 1;
                //delete[] mem;
                //delete[] memory;
                std::cerr << error_message << std::endl;
            }
            catch(...)
            {
                flag_P = 1;
                delete[] mem;
                delete[] memory;
                fclose(fout);
                std::cerr << "Unknown error..." << std::endl;
                return -2;
            }
            if(!flag_P)
                error_P = Pm_error(nodes2, meanings2, N, number_fun);
            else
                error_P = -1;

            if (flag)
            {
                std::cout << "N = " << N << " m = " << m << " number_fun = " << number_fun << " t = " << t << " a = " << a << " b = " << b << std::endl << std::endl;
                std::cout << "counter = " << counter << " h = " << coef[k - 1] << " error_P = " << error_P << std::endl;
            }
            write_result(nodes2, N, meanings2, number_fun, fout, flag_P);
            fclose(fout);

            delete[] mem;
            delete[] memory;
        }
    }
    else 
    {
        fprintf(stderr, "Wrong extra parameters. Must be 'N m number_fun t a b filename'\n");
        return -1;
    }
    return 0;
}

void write_result(double *nodes2, int N, double *meanings2, int number_fun, FILE *fout, int flag_P)
{
    double tmp;
    if(flag_P)
    {
        for(int i = 0; i < 2 * N - 1; i++)
            meanings2[i] = 0.;
    }
    for (int i = 0; i < 2 * N - 1; i++)
    {
        tmp = fun(number_fun, nodes2[i]);
        fprintf(fout, "%20.15lf %20.15lf %20.15lf \n", nodes2[i], meanings2[i], tmp - meanings2[i] );
    }
}

