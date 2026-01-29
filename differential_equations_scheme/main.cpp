#include "solve.h"
#include <iomanip>

int main() 
{
    int N = 1000;
    //double h = 1. / N;
    //double h = 0.1;
    double A = 1000.;
    double y0 = 1.;
    double y1, y2, y3, y4;
    int number_test = 10; // количество тестов
    FILE *fout = nullptr;
    const char *filename_out = "out.txt";
    
    fout = fopen(filename_out, "w");
    if (!fout)
    {
        std::cerr << "Can not open file " << filename_out << std::endl;
        return -1;
    }

    //y = ans(A);

    for(int i = 1; i <= number_test; i++)
    {
        y1 = solution_1(y0, A, N);
        y2 = solution_2(y0, A, N);
        y3 = solution_3(y0, A, N);
        y4 = solution_4(y0, A, N);
        

        //fprintf(fout, "%20.15lf %20.15lf %20.15lf %20.15lf %20.15lf\n", i * log(h0), log(fabs(y1 - y)), log(fabs(y2 - y)), log(fabs(y3 - y)), log(fabs(y4 - y)));
        //fprintf(fout, "%d %e %e %e %e\n", N, fabs(y1 - y), fabs(y2 - y), fabs(y3 - y), fabs(y4 - y));
        fprintf(fout, "%d %e %e %e %e\n", N, y1, y2, y3, y4);
        printf("%d %e %e %e %e\n", N, y1, y2, y3, y4);
        //printf(" %d %e %e %e %e\n\n", N, fabs(y1 - y), fabs(y2 - y), fabs(y3 - y), fabs(y4 - y));
        N *= 2;
    }
    fclose(fout);
    return 0;

}
