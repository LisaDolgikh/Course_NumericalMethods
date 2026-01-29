#include "fourier.h"
#include "functions.h"
#include "matrix.h"

double new_u(double t, double x, double y, int m, int n);
double new_u0(double x, double y, int m, int n);


double new_u(double t, double x, double y, int m, int n)
{
    double tmp = (sin(PI/2 * (2*m - 1) * x)) * (sin(PI/2 * (2*n - 1) * y)) * exp(- PI * PI* t/ 4 * ((2*m-1) *(2*m-1) + (2*n-1) *(2*n-1)));
    return tmp;
}

double new_u0(double x, double y, int m, int n)
{
    double tmp = (sin(PI/2 * (2*m - 1) * x)) * (sin(PI/2 * (2*n - 1) * y));
    return tmp;
}

int main(int argc, char *argv[]) 
{
    int Nx, Ny, Nt, max_N;
    int fix_m, fix_n;
    bool save_nodes = 0;

    double *memory = nullptr;
    double *matrix_d, *matrix_c, *matrix_u, *matrix_uij;
    double *massive_u, *massive_phi;

    double tau, T = 1.;  //residual;
    int number_u = 0; // номер тестовой функции
       
    FILE *fout = nullptr;
    FILE *fout_nodes = nullptr;
    FILE *fout_coef = nullptr;
    //FILE *fout_matrix_d = nullptr;
    //FILE *fout_matrix_c = nullptr;
    //FILE *fout_matrix_u = nullptr;
    const char *filename_out = "out.txt";
    const char *filename_coef = nullptr;


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
    /*
    const char *filename_matrix_d = "matrix_d.txt";

    fout_matrix_d = fopen(filename_matrix_d, "w");
    if (!fout_matrix_d)
    {
        std::cerr << "Can not open file " << filename_matrix_d << std::endl;
        return -1;
    }

    const char *filename_matrix_c = "matrix_c.txt";

    fout_matrix_c = fopen(filename_matrix_c, "w");
    if (!fout_matrix_c)
    {
        std::cerr << "Can not open file " << filename_matrix_c << std::endl;
        return -1;
    }
    

    const char *filename_matrix_u = "matrix_u.txt";

    fout_matrix_u = fopen(filename_matrix_u, "w");
    if (!fout_matrix_u)
    {
        std::cerr << "Can not open file " << filename_matrix_u << std::endl;
        return -1;
    }*/
    

    if (argc == 8) 
    {
        if (toInt(argv[1], &Nx) != 0 || Nx < 3)
        {
            std::cerr << "Wrong parameter 'N_x'" << std::endl;
            return -1;
        }

        if (toInt(argv[2], &Ny) != 0)
        //if (toInt(argv[2], &Ny) != 0 || Ny < 4)
        {
            std::cerr << "Wrong parameter 'Ny' " << std::endl;
            return -1;
        }


        max_N = (Nx > Ny) ? Nx : Ny;
        //printf("%d \n", max_N);

        if (toInt(argv[3], &Nt) != 0 || Nt < 1)
        {
            std::cerr << "Wrong parameter 'Nt' " << std::endl;
            return -1;
        }
        
        if (toInt(argv[4], &number_u) != 0 || number_u < 0 || number_u > 4)
        {
            std::cerr << "Wrong parameter 'number_u'" << std::endl;
            return -1;
        }

        if (toInt(argv[5], &fix_m) != 0 || fix_m < 1 || fix_m > (Nx-1))
        {
            std::cerr << "Wrong parameter 'fix_m' " << std::endl;
            return -1;
        }

        if (toInt(argv[6], &fix_n) != 0 || fix_n < 1 || fix_n > (Ny-1))
        {
            std::cerr << "Wrong parameter 'fix_n' " << std::endl;
            return -1;
        }

        filename_coef = argv[7];

        fout_coef = fopen(filename_coef, "a");

        if (!fout_coef)
        {
            std::cerr << "Can not open file " << filename_coef << std::endl;
            return -1;
        }
        /*
        int k = Ny;
        Nx = k * Nx;
        Ny = Nx;
        Nt = Nx * k;
        */
        

        tau = (double)T / (double)Nt;
        try
        {
            memory = new double[ 3 * Nx * Ny + Nx * Ny * (Nt + 1) + 2 * (max_N + 1)];

            if (memory == nullptr)
            {
                std::cerr << "Can't allocate memory" << std::endl;
                return -1;
            }
            
            matrix_c = memory;                      //  size = Nx * Ny
            matrix_d = matrix_c + Nx * Ny;          //  size = Nx * Ny
            matrix_u = matrix_d + Nx * Ny;          //  size = Nx * Ny

            matrix_uij = matrix_u + Nx * Ny;        //  size = Nx * Ny * (Nt + 1)
            massive_u = matrix_uij + Nx * Ny * (Nt + 1);      //  size = max_N + 1
            massive_phi = massive_u + (max_N + 1);          //  size = max_N + 1

            double hx = 1. / ((double)Nx - 0.5);
            double hy = 1. / ((double)Ny - 0.5);

            //заполняем нулевой слой
            for(int j = 0; j < Ny; j++)
            {
                for(int i = 0; i < Nx; i++)
                {
                    matrix_uij[(j) * (Nx) + i] = new_u0(hx * i, hy * j, fix_m, fix_n);
                    matrix_c[(j) * (Nx) + i] = 0.;
                    matrix_d[(j) * (Nx) + i] = 0.;
                    matrix_u[(j) * (Nx) + i] = 0.;
                }
            }

            //разложили нулевой слой в Фурье
            fourier_to_c(matrix_uij, massive_phi, massive_u, Nx, Ny);
            fprintf(fout_coef, "%e ", matrix_uij[(fix_n) * (Nx) + fix_m]);

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
                fprintf(fout_coef, "%e ", matrix_c[(fix_n) * (Nx) + fix_m]);
            }
            fprintf(fout_coef, "\n");

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
                            double tmp2 = new_u(time_n * tau, i * hx, j * hy, fix_m, fix_n);
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
            //fprintf(fout, "%d %e \n", Nx, residual);
            //printf("Residual = %e \n", residual);
            fclose(fout);
            fclose(fout_coef);
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
        fprintf(stderr, "Wrong extra parameters. Must be 'Nx Ny Nt number_u fix_m fix_n filename_coef'\n");
        return -1;
    }
    return 0;
}
