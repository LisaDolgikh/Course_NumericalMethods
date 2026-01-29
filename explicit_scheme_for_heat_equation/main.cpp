#include "functions.h"

int main(int argc, char *argv[]) 
{
    int N; //число узлов по t
    int M; //число узлов по x
    double h, tau,  residual;
    int number_u = 0; // номер тестовой функции
    double *current_nodes, *previous_nodes, *massive_x;

    bool save_nodes = 0;
    double *memory = nullptr;

    FILE *fout = nullptr;
    FILE *fout_nodes = nullptr;
    const char *filename_out = "out.txt";

    fout = fopen(filename_out, "a");
    if (!fout)
    {
        std::cerr << "Can not open file " << filename_out << std::endl;
        return -1;
    }

    if(save_nodes)
    {
        const char *filename_nodes = "nodes.txt";

        fout_nodes = fopen(filename_nodes, "w");
        if (!fout_nodes)
        {
            std::cerr << "Can not open file " << filename_nodes << std::endl;
            return -1;
        }
    }
    

    if (argc == 3 || argc == 4) 
    {
        if (toInt(argv[1], &N) != 0 || N < 3)
        {
            std::cerr << "Wrong parameter 'N' for time" << std::endl;
            return -1;
        }

        //if (toInt(argv[2], &M) != 0 || M < 3)
        if (toInt(argv[2], &M) != 0)
        {
            std::cerr << "Wrong parameter 'M' for 'x'" << std::endl;
            return -1;
        }

        if(argc == 4)
        {
            if (toInt(argv[3], &number_u) != 0 || number_u < 0 || number_u > 4)
            {
                std::cerr << "Wrong parameter 'number_u'" << std::endl;
                return -1;
            }
        }
        
        //Мы получаем на вход N M number_u, 
        // которые обозначают M k number_u
        int k = M;
        M = N * k;
        N = 2 * M * M;
        


        h = 1. / ((double)M - 0.5);
        tau = 1. / (double) (N);

        if ( 2 * tau > h * h )
        {
            std::cerr << "Wrong parameter 'M' and 'N'. Must be M^2 < N / 2" << std::endl;
            return -1;
        }


        // для неявной схемы - метод прогонки
        try
        {
            memory = new double[ 3 * (M + 1)];

            if (memory == nullptr)
            {
                std::cerr << "Can't allocate memory" << std::endl;
                return -1;
            }
            previous_nodes = memory;   // size = M + 1
            current_nodes = previous_nodes + (M + 1);   // size = M + 1
            massive_x = current_nodes + (M + 1);

            for(int m = 0; m < M + 1; m++)
            {
                massive_x[m] = m * h;
            }

            if(save_nodes)
            {
                for(int m = 0; m < M + 1; m++)
                {
                    if(m != M)
                    {
                        fprintf(fout_nodes,"%e  ", massive_x[m]);
                    }
                    else
                    {
                        fprintf(fout_nodes,"%e \n", massive_x[m]);
                    }
                }
            }


            for(int k = 0; k < M; k++)
            {
                previous_nodes[k] = u0(number_u, k * h); 
            }
            previous_nodes[M] = previous_nodes[M - 1];

            if(save_nodes)
            {
                fprintf(fout_nodes, "%e ", 0. );
                for(int m = 0; m < M + 1; m++)
                {
                    if(m != M)
                    {
                        fprintf(fout_nodes,"%e ", previous_nodes[m]);
                    }
                    else
                    {
                        fprintf(fout_nodes,"%e \n", previous_nodes[m]);
                    }
                }
            }

            for(int n = 0; n < N; n++) 
            // решаем СЛУ для t = i * tay, i=0,...,N-1
            // выражаем (n+1)-ый слой по времени из n-ого слоя
            // n = 0, ..., N - 1
            {
                find_current_nodes(previous_nodes, current_nodes, N, M, n, number_u);

                for(int i = 0; i < M + 1; i++)
                { 
                    previous_nodes[i] = current_nodes[i]; 
                }

                if(save_nodes)
                {
                    fprintf(fout_nodes, "%e ", (n + 1) * tau );
                    for(int m = 0; m < M + 1; m++)
                    {
                        if(m != M)
                        {
                            fprintf(fout_nodes,"%e ", previous_nodes[m]);
                        }
                        else
                        {
                            fprintf(fout_nodes,"%e \n", previous_nodes[m]);
                        }
                    }
                }
            }
    
            residual = error( previous_nodes, number_u, M); // |u*-u|
            fprintf(fout, "%d %e \n", M, residual);
            printf("Residual = %e \n", residual);
            fclose(fout);
            if(save_nodes)
            {
                fclose(fout_nodes);
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
            delete[] memory;
            return -2;
        }
        delete[] memory;
    }
    else 
    {
        fprintf(stderr, "Wrong extra parameters. Must be: N M (number_u) (M^2 < N / 2 )\n");
        manual(argv[0]);
        return -1;
    }
    return 0;
}

void manual (const char *str)
{
    const char *txt = 
        "Functions:                                     \n"
        "f0(x)=0 / your_test                      	    \n"
        "f1(x)=(x^2 - 2x)*exp(- PI^2 t/4)               \n"
        "f2(x)=(x^3 - 3x)*exp(-t)                       \n"
        "f3(x)=sin(PI*x/2)*exp(- PI^2 t/4)              \n"
        "f4(x)=x*exp(-x)*exp(t)                         \n"
        "For the convergence order test use M k number_u\n";
    fprintf(stderr, "Input: %s N M (number_u) \n%s\n", str, txt);
}