#include "splitting.h"
#include "integration.h"
#include "functions.h"

void manual (const char *str);

int main(int argc, char *argv[]) 
{
    double x1, x2, y1, y2;
    int flag = 1; // 1 - печатать разультаты в консоль; 0 - не печатать
    int N, number_fun;
    double integ, quadrature, R;
    fun_t f, functions[] = {fun1, fun2, fun3, fun4, fun5};
    FILE *fout, *fres = nullptr;
    const char *filename_out = nullptr;

    int count_nodes;
    double *mem_double = nullptr, *nodes_x, *nodes_y;
    int *mem_int = nullptr, *triangle_1, *triangle_2, *triangle_3;

    if (argc == 8) 
    {
        if (toDouble(argv[1], &x1) != 0)
        {
            std::cerr << "Wrong parameter 'x1'" << std::endl;
            return -1;
        }

        if (toDouble(argv[2], &y1) != 0 )
        {
            std::cerr << "Wrong parameters 'y1'" << std::endl;
            return -1;
        }

        if (toDouble(argv[3], &x2) != 0 || ! (x2 > x1))
        {
            std::cerr << "Wrong parameter 'x2'" << std::endl;
            return -1;
        }

        if (toDouble(argv[4], &y2) != 0 || ! (y2 > y1))
        {
            std::cerr << "Wrong parameters 'y2'" << std::endl;
            return -1;
        }

        if (toInt(argv[5], &N) != 0 || N < 1)
        {
            std::cerr << "Wrong parameter 'N'" << std::endl;
            return -1;
        }

        filename_out = argv[6];

        if (toInt(argv[7], &number_fun) != 0 || number_fun < 0 || number_fun > 5)
        {
            std::cerr << "Wrong parameter 'number_fun'" << std::endl;
            return -1;
        }
        f = functions[number_fun - 1];

		//---------------------------------------------------------------------------------------------------
         //вычисляем точное значение интеграла
        if(number_fun == 1) //x + y
        {
            integ = (x2*x2*y2 + x2*y2*y2 - x1*x1*y1 - x1*y1*y1 ) / 2.;
        }

        else if(number_fun == 2) //x * x + y * y
        {
            integ = (x2*x2*x2*y2 + x2*y2*y2*y2 - x1*x1*x1*y1 - x1*y1*y1*y1 ) / 3.;
        }

        else if(number_fun == 3) //x * x * x * x + x * x * y * y + y * y * y *y
        {
            integ = x2*y2 * (pow(x2, 4) + pow(y2, 4)) / 5. + pow(x2, 3)* pow(y2, 3) / 9. - x1*y1 * (pow(x1, 4) + pow(y1, 4)) / 5. - pow(x1, 3)* pow(y1, 3) / 9. ;
        } 

        else if(number_fun == 4) //x - y
        {
            integ = (x2*x2*y2 - x2*y2*y2 - x1*x1*y1 + x1*y1*y1 ) / 2.;
        }

        else //x * y
        {
            integ = (x2 * x2 * y2 * y2 - x1 * x1 * y1 * y1) / 4.;
        }
		//----------------------------------------------------------------------------------------------------



        fres = fopen("res.txt", "w");
        if (!fres)
        {
            std::cerr << "Can not open file " << filename_out << std::endl;
            return -1;
        }

        for (int i = 0; i < 10; i++)
        {
            count_nodes = (N + 1) * (N + 1);
            fout = fopen(filename_out, "w");
            if (!fout)
            {
                std::cerr << "Can not open file " << filename_out << std::endl;
                return -1;
            }
            splitting(x1, x2, y1, y2, N, fout);
            fclose(fout);


            try
            {
                mem_double = new double[ 2 * count_nodes];
                mem_int = new int[3 * 2 * N * N];

                if (mem_double == nullptr || mem_int == nullptr)
                {
                    std::cerr << "Can't allocate memory" << std::endl;
                    return -1;
                }

                nodes_x = mem_double; //координаты вершин по x, размер (N + 1)* (N + 1)
                nodes_y = nodes_x + count_nodes; //координаты вершин по y

                triangle_1 = mem_int;
                triangle_2 = triangle_1 + 2 * N* N;
                triangle_3 = triangle_2 + 2 * N* N;

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
				delete[] mem_double;
				delete[] mem_int;
                fclose(fout);
                return -2;
            }



            fout = fopen(filename_out, "r");
            if (!fout)
            {
                std::cerr << "Can not open file " << filename_out << std::endl;
				delete[] mem_double;
				delete[] mem_int;
                return -1;
            }
            fscanf(fout, "Число вершин: %d\n", &count_nodes);
            fscanf(fout, "Число внутренних ребёр: %*d\n");
            fscanf(fout, "Число граниченых ребёр: %*d\n");

            for(int i = 0; i < count_nodes; i++)
            {
                fscanf(fout, "%*d: %lf %lf \n", &nodes_x[i], &nodes_y[i]);
            }

            for(int i = 0; i < 2 * N * N; i++)
            {
                fscanf(fout, "%*d: %d %d %d \n", &triangle_1[i], &triangle_2[i], &triangle_3[i] );
            }
            fclose(fout);

            quadrature = integrate(N, f, nodes_x, nodes_y, triangle_1, triangle_2, triangle_3 );
			R = fabs(integ - quadrature);

			delete[] mem_double;
			delete[] mem_int;
            if(flag)
            {
                //std::cout << "(x1, y1) = ( " << x1 << " , " << y1 << " ) ;  (x2, y2) = ( " << x2 << " , " << y2 << " )" << std::endl;
				std::cout << "N = " << N << " number_fun = " << number_fun << std::endl;
                std::cout << "Quadrature(f) = " << std::fixed << quadrature << std::endl;
                std::cout << "Integral(f) = " << std::fixed << integ << std::endl;
                std::cout << "R(f) = " << std::fixed << R  << std::endl << std::endl;
            }
			if(R > EPS)
			{
				fprintf(fres, "%e %e \n",log((double)(N)), log(R));
			}
			else
			{
				fprintf(fres, "%e %e \n",log((double)(N)), 0.);
			}

            N = N * 2;
        }
		fclose(fres);

    }
    else 
    {
        fprintf(stderr, "Wrong extra parameters. Must be 'x1 y1 x2 y2 N filename number_fun'\n");
        manual(argv[0]);
        return -1;
   }
    return 0;
}

void manual (const char *str)
{
    const char *txt = 
        "Functions:                                           \n"
        "f1(x) = x + y                                        \n"
        "f2(x) = x * x + y * y                                \n"
        "f3(x) = x^4 + x^2 y^2 + y^4                          \n"
        "f4(x) = x - y                                        \n"
        "f5(x) = x * y                                        \n";

    fprintf(stderr, "Input: %s x1 y1 x2 y2 N filename number_fun\n%s\n", str, txt);
}
