#include "fourier.h"

int main(int argc, char *argv[]) 
{
    int N; //число узлов
    int number_fun; // номер тестовой функции
    int number_test = 10; // количество тестов для определения порядка сходимости

    FILE *fout = nullptr, *pval = nullptr;
    const char *filename = nullptr;

    int flag = 1; // 0 - не вычисляем норму; 1 - вычисляем норму

    double *mem, *massive_c, *massive_dots, *massive_phi, *massive_u;
    double *massive_N, *massive_norm, *massive_time;

    clock_t s, e;

    if (argc == 4) 
    {
        if (toInt(argv[1], &N) != 0 || N < 3)
        {
            std::cerr << "Wrong parameter 'N'" << std::endl;
            return -1;
        }

        if (toInt(argv[2], &number_fun) != 0 || number_fun < 1 || number_fun > 6)
        {
            std::cerr << "Wrong parameter 'number_fun'" << std::endl;
            return -1;
        }

        filename = argv[3];

        fout = fopen(filename, "w");

        if (!fout)
        {
            std::cerr << "Can not open file " << filename << std::endl;
            return -1;
        }

        try
        {
            mem = new double[(N * number_test)*(N * number_test) + (3 * (N + 1)) * (number_test) + 3 * number_test] ;

            if (mem == nullptr)
            {
                std::cerr << "Can't allocate memory" << std::endl;
                return -1;
            }
            massive_c = mem;
            massive_dots = massive_c + (N) * (number_test) * (N) * (number_test);
            massive_u = massive_dots + (N + 1) * (number_test);
            massive_phi = massive_u + (N + 1) * (number_test);

            massive_N = massive_phi + (N + 1) * (number_test);
            massive_norm = massive_N + (number_test);
            massive_time = massive_norm + (number_test);            
        }
        catch (std::bad_alloc &)
        {
            std::cerr << "Memory allocation error"<<std::endl;
            return -2;
        }

        catch(...)
        {
            std::cerr << "Unknown error..." << std::endl;
            return -2;
        }

	    for(int j = 2; j <= number_test; j++)
	    {
		    massive_N[j-1] = j * N;

		    s = clock();
		    fourier_to_c(massive_c, massive_phi, massive_u, massive_dots, number_fun, j * N);
		    e = clock();

		    massive_time[j-1] = (double)(e - s) / CLOCKS_PER_SEC;

            if(flag) //flag == 1 -> вычисляем норму
                massive_norm[j-1] = norma(massive_c, number_fun, j * N);
            else
                massive_norm[j-1] = 0.;
	    }

        massive_N[0] = N;
        s = clock();
        fourier_to_c(massive_c, massive_phi, massive_u, massive_dots, number_fun, N);
        e = clock();
        massive_time[0] = (double)(e - s) / CLOCKS_PER_SEC;
        if(flag) //flag == 1 -> вычисляем норму
            massive_norm[0] = norma(massive_c,number_fun, N);
        else
        {
            massive_norm[0] = 0.;
        }

	    std::cout << "number_fun = " << number_fun << std::endl << std::endl;

        for(int j = 0; j < number_test; j++)
	    {
		    std::cout << "Время при N = " << (j+1) * N << " : " << std::fixed << massive_time[j] << std::endl;
			if(flag) //flag == 1 -> вычисляем норму
                std::cout << "Погрешность при N = " << (j+1) * N << " : " << std::scientific << massive_norm[j] << std::endl << std::endl;
	    }
        // запись в файл коэффициентов
		for(int i = 1; i <= N*N; i++)
		{
			fprintf(fout, "%20.15lf ", massive_c[i-1]);
			if((i % N == 0) && (i != 1))
				fprintf(fout, "\n");
		}
		fclose(fout);

        //print_result(massive_c, massive_dots, number_fun, N);

        // Для печати коэффициентов
		/*for(int i = 1; i <= N*N; i++)
		{
			printf("%20.15lf ", massive_c[i-1]);
			if((i % N == 0) && (i != 1))
				printf( "\n");
		}*/

        pval = fopen("pval.txt", "w");

	    if(pval == nullptr)
	    {
		    std::cerr << "Can't open file" << std::endl;
		    delete[] mem;
		    return -1;
	    }

	    for(int j = 1; j <= number_test; j++)
	    {
		    fprintf(pval, "%20.15lf %20.15lf \n", massive_N[j-1], massive_norm[j-1]);
	    }

	    fclose(pval);
        delete[] mem;
    }
    else 
    {
        fprintf(stderr, "Wrong extra parameters. Must be 'N number_fun filename'\n");
        return -1;
    }
    return 0;

}

int toInt(const char *str, int *value) 
{
    long result;
    char *e;
    errno = 0;
    result = strtol(str, &e, 10);

    if (errno != 0 || *e != '\0') 
        return -1;

    if (INT_MIN <= result && result <= INT_MAX) 
    {
        *value = (int) result;
        return 0;
    }
    return -1;
}

void print_result(double *massive_c, double *massive_dots, int number_fun, int N)
{	
	double x_i, y_j, tmp;
    //double x_i1, y_j1, tmp1;
	
	printf("      УЗЕЛ X    |      УЗЕЛ Y     |      ФУРЬЕ      |      ФУНКЦИЯ    |     РАЗНОСТЬ\n");
	printf("--------------------------------------------------------------------------------------\n");

	for(int i = 0; i < N; i++)
	{
		for(int j = 0; j < N; j++)
		{
			x_i = massive_dots[i];
			//x_i1 = x_i / 2. + massive_dots[i+1] / 2.;
			
			y_j = massive_dots[j];
			//y_j1 = y_j / 2. + massive_dots[j+1] / 2.;

			tmp = back_fourier(massive_c, x_i, y_j, N);
			//tmp1 = back_fourier(massive_c, x_i1, y_j1, N);
		
			printf("%15.10lf | %15.10lf | %15.10lf | %15.10lf | %15.10lf \n", x_i, y_j, tmp, fun(number_fun, x_i, y_j), fabs(tmp - fun(number_fun, x_i, y_j)));
			//printf("%15.10lf | %15.10lf | %15.10lf | %15.10lf | %15.10lf \n", x_i1, y_j1, tmp1, fun(number_fun, x_i1, y_j1), fabs(tmp1 - fun(number_fun, x_i1, y_j1)));
        }
		
	}
}
