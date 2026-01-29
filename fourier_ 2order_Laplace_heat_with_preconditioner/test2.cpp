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
    int Nx, Ny, max_N;
    int fix_m, fix_n;
    double tau = 0.001;

    double *memory = nullptr;
    double *matrix_c, *matrix_u, *matrix_u_2;
    double *massive_u, *massive_phi;
    double *previous_nodes;
    double *matrix_c_1;

    double p_const = 1.;
    int number_u = 0; // номер тестовой функции
       
  

    if (argc == 6) 
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
        
        if (toInt(argv[3], &number_u) != 0 || number_u < 0 || number_u > 4)
        {
            std::cerr << "Wrong parameter 'number_u'" << std::endl;
            return -1;
        }

        if (toInt(argv[4], &fix_m) != 0 || fix_m < 1 || fix_m > (Nx-1))
        {
            std::cerr << "Wrong parameter 'fix_m' " << std::endl;
            return -1;
        }

        if (toInt(argv[5], &fix_n) != 0 || fix_n < 1 || fix_n > (Ny-1))
        {
            std::cerr << "Wrong parameter 'fix_n' " << std::endl;
            return -1;
        }

        try
        {
            memory = new double[ 5 * Nx * Ny + 2 * (max_N + 1)];

            if (memory == nullptr)
            {
                std::cerr << "Can't allocate memory" << std::endl;
                return -1;
            }
            
            matrix_c = memory;                              //  size = Nx * Ny
            previous_nodes = matrix_c + Nx * Ny;          //  size = Nx * Ny
            matrix_u = previous_nodes + Nx * Ny;          //  size = Nx * Ny
            matrix_u_2 = matrix_u + Nx * Ny;               //  size = Nx * Ny
            matrix_c_1 = matrix_u_2 + Nx*Ny;

            massive_u = matrix_c_1 + Nx * Ny;      //  size = max_N + 1
            massive_phi = massive_u + (max_N + 1);          //  size = max_N + 1

            double hx = 1. / ((double)Nx - 0.5);
            double hy = 1. / ((double)Ny - 0.5);

            //заполняем нулевой слой
            for(int j = 0; j < Ny; j++)
            {
                for(int i = 0; i < Nx; i++)
                {
                    previous_nodes[(j) * (Nx) + i] = new_u0(hx * i, hy * j, fix_m, fix_n);
                    matrix_c[(j) * (Nx) + i] = 0.;
                    matrix_u[(j) * (Nx) + i] = 0.;
                }
            }

            mult_matrix_Au(previous_nodes, matrix_u, tau, Nx, Ny);

            printf("Matrica value in nodes Au \n");
            for(int j = 0; j < Ny; j++)
            {
                for(int i = 0; i < Nx; i++)
                {
                    printf(" %e  ", matrix_u[(j) * (Nx) + i]);
                    matrix_c_1[(j) * (Nx) + i] = matrix_u[(j) * (Nx) + i];
                }
                printf(" \n");
            }
            printf(" \n");
            printf(" \n");

            fourier_to_c(matrix_c_1, massive_phi, massive_u, Nx, Ny);
            /*printf("Matrica coef fourier Au \n");
            for(int j = 0; j < Ny; j++)
            {
                for(int i = 0; i < Nx; i++)
                {
                    printf(" %e  ", matrix_c_1[(j) * (Nx) + i]);
                }
                printf(" \n");
            }
            printf(" \n");
            printf(" \n");
            printf(" \n");*/


            fourier_to_c(previous_nodes, massive_phi, massive_u, Nx, Ny);
            make_c_from_f(previous_nodes, matrix_c, Nx, Ny, tau, p_const);

            
            /*printf("Matrica coef fourier \n");
            for(int j = 0; j < Ny; j++)
            {
                for(int i = 0; i < Nx; i++)
                {
                    printf(" %e  ", matrix_c[(j) * (Nx) + i]);
                }
                printf(" \n");
            }
            printf(" \n");
            printf(" \n");
            printf(" \n");*/

            for(int j = 0; j < Ny; j++)
            {
                for(int i = 0; i < Nx; i++)
                {
                    int index = (j) * (Nx) + i;
                    matrix_u_2[index] = back_fourier(matrix_c, i * hx, j * hy, Nx, Ny);
                    matrix_u_2[index] += (- p_const + p(i*hx, j*hy)) * new_u0(hx * i, hy * j, fix_m, fix_n); 
                }
            }

             printf("Matrica value in nodes fourier \n");
             for(int j = 0; j < Ny; j++)
            {
                for(int i = 0; i < Nx; i++)
                {
                    printf(" %e  ", matrix_u_2[(j) * (Nx) + i]);
                }
                printf(" \n");
            }


            double res = 0., max = 0.;
            int i_max, j_max;
            for(int j = 0; j < Ny; j++)
            {
                for(int i = 0; i < Nx; i++)
                {
                    int index = (j) * (Nx) + i;
                    res = fabs(matrix_u_2[index] - matrix_u[index]);
                    if(res > max)
                    {
                        max = res;
                        i_max = i;
                        j_max = j;
                    }
                }
            }

            printf("i_max = %d    j_max= %d \n", i_max, j_max);
            printf("Residual = %e  u_matr = %e   u_four = %e  %e\n", max, matrix_u[(j_max) * (Nx) + i_max], matrix_u_2[(j_max) * (Nx) + i_max],  (matrix_u[(j_max) * (Nx) + i_max]/res) );
           
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
