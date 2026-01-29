#include "splitting.h"

void splitting(double x1, double x2, double y1, double y2, int N, FILE *fout)
{

    double hx = (x2 - x1) / N;
    double hy = (y2 - y1) / N;
    int leftdown = 0;
    int number = 1;     
    fprintf(fout, "Число вершин: %d\n", (N + 1) * (N + 1));
    fprintf(fout, "Число внутренних ребёр: %d\n", 2 * (N - 1) * N + N * N);
    fprintf(fout, "Число граниченых ребёр: %d\n", 4 * N);

    for (int i = 0; i < (N + 1) * (N + 1); i++)
    {
        // номер вершины, её координата по x, её координата по y
        fprintf(fout, "%d: %20.15lf %20.15lf \n", i + 1, (i % (N + 1)) * hx + x1, (i / (N + 1)) * hy + y1);
    }

    for (int j = 1; j < N + 1; j++)
    {
        for (int i = 1; i < N + 1; i++)
        {
            // номер треугольника, номера вершин (3 шт)
            leftdown = i + (j - 1) * (N + 1);
            fprintf(fout, "%d: %d %d %d \n", 2 * (i + (j - 1) * N) - 1, leftdown, leftdown + 1, leftdown + N + 1);
            fprintf(fout, "%d: %d %d %d \n", 2 * (i + (j - 1) * N), leftdown + 1, leftdown + N + 1, leftdown + N + 2);
        }
    }

    for (int j = 1; j < N + 1; j++)
    {
        for (int i = 1; i < N + 1; i++) 
        {
            leftdown = i + (j - 1) * (N + 1);
            if(i == 1 && j == 1) 
            {
                // номер внутр ребра, номера вершин (2 шт)
                fprintf(fout, "%d: %d %d \n", number, 2, N + 2);
                number++;
            }
            else if(i == 1) 
            {
                // номер внутр ребра, номера вершин (2 шт)
                fprintf(fout, "%d: %d %d\n", number, leftdown, leftdown + 1);
                number++;
                fprintf(fout, "%d: %d %d\n", number, leftdown + 1, leftdown + N + 1);
                number++;
            }
            else if(j == 1) 
            {
                // номер внутр ребра, номера вершин (2 шт)
                fprintf(fout, "%d: %d %d\n", number, leftdown, leftdown + N + 1);
                number++;
                fprintf(fout, "%d: %d %d\n", number, leftdown + 1, leftdown + N + 1);
                number++;
            }
            else 
            {
                // номер внутр ребра, номера вершин (2 шт)
                fprintf(fout, "%d: %d %d\n", number, leftdown, leftdown + N + 1);
                number++;
                fprintf(fout, "%d: %d %d\n", number, leftdown, leftdown + 1);
                number++;
                fprintf(fout, "%d: %d %d\n", number, leftdown + 1, leftdown + N + 1);
                number++;
            }
        }
    }

    number = 1;
    //номера граничных ребёр
    fprintf(fout, "Граничные ребра \n");
    for (int j = 1; j < N + 1; j++)
    {
        //номера граничных ребёр горизонтальных, низ
        fprintf(fout, "%d: %d %d\n", number, j, j + 1);
        number++;
    }

    for (int j = 0; j < N; j++)
    {
        //номера граничных ребёр вертикальных, лево, право
        fprintf(fout, "%d: %d %d\n", number, j * (N + 1) + 1, j * (N + 1) + N + 2);
        number++;
        fprintf(fout, "%d: %d %d\n", number, j * (N + 1) + 1 + N, j * (N + 1) + 1 + N + N + 1);
        number++;
    }

    for (int j = 1; j < N + 1; ++j)
    {
        //номера граничных ребёр горизонтальных, верх
        fprintf(fout, "%d: %d %d\n", number, (N + 1) * N + j, (N + 1) * N + 1 + j);
        number++;
    }
}
