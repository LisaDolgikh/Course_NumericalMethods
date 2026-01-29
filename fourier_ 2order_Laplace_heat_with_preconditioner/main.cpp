 #include "fourier.h"
#include "functions.h"

int main(int argc, char *argv[]) 
{
    int Nx, Ny, Nt, max_N;
    bool save_nodes = 1;

    double *memory = nullptr;
    double *matrix_d, *matrix_c, *matrix_uij;
    double *massive_u, *massive_phi;
    double *matrix_u, *previous_nodes;
    double *vector_b, *help_matrix;

    double theta = 1.0;
    double p_const = 0.;
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

        tau = (double)T / (double)Nt;
        try
        {
            memory = new double[ 6 * Nx * Ny + Nx * Ny * (Nt + 1) + 2 * (max_N + 1)];

            if (memory == nullptr)
            {
                std::cerr << "Can't allocate memory" << std::endl;
                return -1;
            }
    
            matrix_c = memory;                      //  size = Nx * Ny
            matrix_d = matrix_c + Nx * Ny;          //  size = Nx * Ny
            help_matrix = matrix_d + Nx*Ny;         //  size = Nx * Ny
            matrix_u = help_matrix + Nx * Ny;       //  size = Nx * Ny
            previous_nodes = matrix_u + Nx * Ny;    //  size = Nx * Ny
            vector_b = previous_nodes + Nx * Ny;

            matrix_uij = vector_b + Nx * Ny;                //  size = Nx * Ny * (Nt + 1)
            massive_u = matrix_uij + Nx * Ny * (Nt + 1);    //  size = max_N + 1
            massive_phi = massive_u + (max_N + 1);          //  size = max_N + 1



            double hx = 1. / ((double)Nx - 0.5);
            double hy = 1. / ((double)Ny - 0.5);

            //заполняем нулевой слой
            for(int j = 0; j < Ny; j++)
            {
                for(int i = 0; i < Nx; i++)
                {
                    int index = (j) * (Nx) + i;
                    matrix_uij[index] = u0(number_u, hx * i, hy * j);
                    previous_nodes[index] = matrix_uij[index];
                    matrix_c[index] = 0.;
                    matrix_d[index] = 0.;
                }
            }

            //разложили нулевой слой в Фурье
            fourier_to_c(matrix_uij, massive_phi, massive_u, Nx, Ny);

            if(save_nodes)
            {
                for(int j = 0; j < Ny; j++)
                {
                    for(int i = 0; i < Nx; i++)
                    {
                        double tmp1 = back_fourier(matrix_uij, i * hx, j * hy, Nx, Ny);
                        double tmp2 = u(number_u, 0., i * hx, j * hy);
                        fprintf(fout_nodes, "%e %e %e %e %e \n", 0., (i * hx), (j * hy), tmp1, tmp2);
                    }
                }
            }

            
            for(int time_n = 1; time_n <= Nt; time_n++)
            {
                make_d_from_f(matrix_d, massive_phi, massive_u, Nx, Ny, number_u, (tau * time_n));
                make_c_from_d_and_previous(matrix_d, matrix_c, matrix_uij + (time_n - 1) * Nx * Ny, Nx, Ny, tau, p_const);
                // выше создали u_ij^{1, 0}
                 

                // запускаем Bsolver, передавая туда значения в узлах (не коэффициенты Фурье)
                for(int j = 0; j < Ny; j++)
                {
                    for(int i = 0; i < Nx; i++)
                    {
                        int index = (j) * (Nx) + i;
                        matrix_u[index] = back_fourier(matrix_c, i * hx, j * hy, Nx, Ny);
                        vector_b[index] = previous_nodes[index] / tau + fun(number_u, (time_n * tau), hx * i, hy * j);
                    }
                } 
                method_BSolver(matrix_u, vector_b, Nx, Ny, tau, theta, p_const, massive_phi, massive_u, matrix_d, help_matrix);
                for(int j = 0; j < Ny; j++)
                {
                    for(int i = 0; i < Nx; i++)
                    {
                        int index = (j) * (Nx) + i;
                        matrix_uij[time_n * Nx * Ny + index] = matrix_u[index];
                        previous_nodes[index] =  matrix_u[index];
                        fprintf(fout_nodes, "%e %e %e %e %e \n", (tau * time_n), (i * hx), (j * hy), matrix_u[index], u(number_u, time_n * tau, i * hx, j * hy));
                    }
                } 
                fourier_to_c(matrix_uij + time_n * Nx * Ny, massive_phi, massive_u, Nx, Ny);
            }
            //residual = error(matrix_c, number_u, Nx, Ny, T);
            residual = error_2(matrix_u, number_u, Nx, Ny, T);
            fprintf(fout, "%d %e \n", Nx, residual);
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
        fprintf(stderr, "Wrong extra parameters. Must be 'Nx Ny Nt T number_u'\n");
        return -1;
    }
    return 0;
}

