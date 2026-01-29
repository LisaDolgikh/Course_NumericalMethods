#include "splitting.h"
#include "functions.h"

int main(int argc, char *argv[]) 
{
    double x1, x2, y1, y2;
    int N;
    //int flag = 1; // 1 - печатать разультаты в консоль; 0 - не печатать

    FILE *fout = nullptr;
    const char *filename_out = nullptr;

    if (argc == 7) 
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
        fout = fopen(filename_out, "w");
        if (!fout)
        {
            std::cerr << "Can not open file " << filename_out << std::endl;
            return -1;
        }

        splitting(x1, x2, y1, y2, N, fout);

        fclose(fout);

    }
    else 
    {
        fprintf(stderr, "Wrong extra parameters. Must be 'x1 y1 x2 y2 N filename'\n");
        return -1;
    }
    return 0;
}

