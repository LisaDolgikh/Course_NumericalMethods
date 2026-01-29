#include "fourier.h"
#include "functions.h"

int main(int argc, char *argv[]) 
{
    int Nx, Ny, Nt, max_N;
    bool save_nodes = 0;

    double *memory = nullptr;
    double *matrix_d, *matrix_c, *matrix_uij;
    double *massive_u, *massive_phi;

    double tau, T,  residual;
    int number_u = 0; // номер тестовой функции
       
    FILE *fout = nullptr;
    FILE *fout_nodes = nullptr;
    //FILE *fout_matrix_d = nullptr;
    //FILE *fout_matrix_c = nullptr;
    //FILE *fout_matrix_u = nullptr;
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

    /*const char *filename_matrix_d = "matrix_d.txt";

    fout_matrix_d = fopen(filename_matrix_d, "w");
    if (!fout_matrix_d)
    {
        std::cerr << "Can not open file " << filename_matrix_d << std::endl;
        return -1;
    }*/

    /*const char *filename_matrix_c = "matrix_c.txt";

    fout_matrix_c = fopen(filename_matrix_c, "w");
    if (!fout_matrix_c)
    {
        std::cerr << "Can not open file " << filename_matrix_c << std::endl;
        return -1;
    }*/

    if (argc == 6) 
    {
        if (toInt(argv[1], &Nx) != 0 || Nx < 3)
        {
            std::cerr << "Wrong parameter 'Nx'" << std::endl;
            return -1;
        }

        if (toInt(argv[2], &Ny) != 0 || Ny < 3)
        {
            std::cerr << "Wrong parameter 'Ny' " << std::endl;
            return -1;
        }


        max_N = (Nx > Ny) ? Nx : Ny;

        if (toInt(argv[3], &Nt) != 0 || Nt < 1)
        {
            std::cerr << "Wrong parameter 'Nt' " << std::endl;
            return -1;
        }

        if (toDouble(argv[4], &T) != 0 || T < 0)
        {
            std::cerr << "Wrong parameter 'T'" << std::endl;
            return -1;
        }
        
        if (toInt(argv[5], &number_u) != 0 || number_u < 0 || number_u > 4)
        {
            std::cerr << "Wrong parameter 'number_u'" << std::endl;
            return -1;
        }

        /*
        int k = Ny;
        Nx = k * Nx;
        Ny = Nx;
        Nt = Nx * k;*/
        Nt = Nx * Nx;
        
        

        tau = (double)T / (double)Nt;
        try
        {
            memory = new double[ 2 * Nx * Ny + Nx * Ny * (Nt + 1) + 2 * (max_N + 1)];

            if (memory == nullptr)
            {
                std::cerr << "Can't allocate memory" << std::endl;
                return -1;
            }
            
            matrix_c = memory;                      //  size = Nx * Ny
            matrix_d = matrix_c + Nx * Ny;          //  size = Nx * Ny

            matrix_uij = matrix_d + Nx * Ny;        //  size = Nx * Ny * (Nt + 1)
            massive_u = matrix_uij + Nx * Ny * (Nt + 1);      //  size = max_N + 1
            massive_phi = massive_u + (max_N + 1);          //  size = max_N + 1

            double hx = 1. / ((double)Nx - 0.5);
            double hy = 1. / ((double)Ny - 0.5);

            //заполняем нулевой слой
            for(int j = 0; j < Ny; j++)
            {
                for(int i = 0; i < Nx; i++)
                {
                    matrix_uij[(j) * (Nx) + i] = u0(number_u, hx * i, hy * j);
                    matrix_c[(j) * (Nx) + i] = 0.;
                    matrix_d[(j) * (Nx) + i] = 0.;
                }
            }

            //разложили нулевой слой в Фурье
            fourier_to_c(matrix_uij, massive_phi, massive_u, Nx, Ny);

            /*
            for(int j = 0; j < Ny; j++)
            {
                for(int i = 0; i < Nx; i++)
                {
                    fprintf(fout_matrix_c, " %e  ", matrix_uij[(j) * (Nx) + i]);
                }
                fprintf(fout_matrix_c, " \n");
            }*/

            /*
            printf( " xi   yj   back_fourier   real_u   error \n");
            for(int j = 0; j < Ny; j++)
            {
                for(int i = 0; i < Nx; i++)
                {
                    double tmp1 = back_fourier(matrix_uij, i * hx, j * hy, Nx, Ny);
                    double tmp2 = u(number_u, 0., i * hx, j * hy);
                    printf(" %e %e %e %e %e\n", (i * hx), (j * hy), tmp1, tmp2, tmp2-tmp1);
                }
                printf("\n");
                printf("\n");
                printf("\n");
            }*/

            for(int time_n = 1; time_n <= Nt; time_n++)
            {
                make_d_from_f(matrix_d, massive_phi, massive_u, Nx, Ny, number_u, (tau * time_n));
                make_c_from_d_and_previous(matrix_d, matrix_c, matrix_uij + (time_n - 1) * Nx * Ny, Nx, Ny, tau);

                for(int j = 0; j < Ny; j++)
                {
                    for(int i = 0; i < Nx; i++)
                    {
                        matrix_uij[time_n * Nx * Ny + (j) * (Nx) + i] = matrix_c[(j) * (Nx) + i];
                    }
                }                
                
                /*
                printf( " xi   yj   back_fourier   real_u   error \n");
                printf( " time = %d \n", time_n);
                for(int j = 0; j < Ny; j++)
                {
                    for(int i = 0; i < Nx; i++)
                    {
                        double tmp1 = back_fourier(matrix_uij+ time_n * Nx *Ny, i * hx, j * hy, Nx, Ny);
                        double tmp2 = u(number_u, time_n * tau, i * hx, j * hy);
                        printf(" %e %e %e %e %e\n", (i * hx), (j * hy), tmp1, tmp2, tmp2-tmp1);
                    }
                    printf("\n");
                    printf("\n");
                    printf("\n");
                }*/

                /*
                fprintf(fout_matrix_d, "%d \n", time_n);
                fprintf(fout_matrix_c, " \n");
                fprintf(fout_matrix_c, " \n");
                fprintf(fout_matrix_c, " \n");
                for(int j = 0; j < Ny; j++)
                {
                    for(int i = 0; i < Nx; i++)
                    {
                        fprintf(fout_matrix_d, " %e  ", matrix_d[(j) * (Nx) + i]);
                        fprintf(fout_matrix_c, " %e  ", matrix_c[(j) * (Nx) + i]);
                    }
                    fprintf(fout_matrix_d, " \n");
                    fprintf(fout_matrix_c, " \n");
                }*/
            }

            if(save_nodes)
            {
                fprintf(fout_nodes, "time  xi   yj   back_fourier   real_u   error \n");
                for(int time_n = 0; time_n <= Nt ; time_n++)
                {
                    for(int j = 0; j < Ny; j++)
                    {
                        for(int i = 0; i < Nx; i++)
                        {
                            double tmp1 = back_fourier(matrix_uij + time_n * Nx *Ny, i * hx, j * hy, Nx, Ny);
                            double tmp2 = u(number_u, time_n * tau, i * hx, j * hy);
                            fprintf(fout_nodes, "%e %e %e %e %e %e\n", (tau * time_n), (i * hx), (j * hy), tmp1, tmp2, tmp2-tmp1);
                        }
                        fprintf(fout_nodes, "\n");
                    }
                    fprintf(fout_nodes, "\n");
                    fprintf(fout_nodes, "\n");
                    fprintf(fout_nodes, "\n");
                }
            }
            //residual = error(matrix_c, number_u, Nx, Ny, T);
            int i_max = 0, j_max = 0;
            residual = error_plus(matrix_c, number_u, Nx, Ny, T, &i_max, &j_max);
            double res = back_fourier(matrix_c, i_max * hx, j_max*hy, Nx, Ny);
            fprintf(fout, "%d %e \n", Nx, residual);
            printf("Residual = %e   %e   %e\n", residual, res, (residual/res) );
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
        fprintf(stderr, "Wrong extra parameters. Must be 'Nx Ny Nt T number_u'\n");
        return -1;
    }
    return 0;
}

