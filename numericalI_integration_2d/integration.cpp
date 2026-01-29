#include "integration.h"

double integrate(int N, double (*f)(double, double), double *nodes_x, double *nodes_y, int *triangle_1, int *triangle_2, int *triangle_3)
{
    //double x = 0., y = 0.;
    double x1, x2, x3, y1, y2, y3, tmp;
    double res = 0.;

    for(int i = 0; i < 2 * N * N; i++)
    {
        //std::cout << "triangle_1[i] = " << triangle_1[i] << " triangle_2[i] = " << triangle_2[i] << " triangle_3[i] = " << triangle_3[i] <<std::endl;
        //std::cout << "nodes_x[ triangle_1[i]] = " << nodes_x[triangle_1[i] - 1] << " nodes_x[triangle_2[i]] = " << nodes_x[triangle_2[i] - 1] << " nodes_x[triangle_3[i]] = " << nodes_x[triangle_3[i] - 1] << std::endl;
        //std::cout << "nodes_y[ triangle_1[i]] = " << nodes_y[triangle_1[i] - 1] << " nodes_y[triangle_2[i]] = " << nodes_y[triangle_2[i] - 1] << " nodes_y[triangle_3[i]] = " << nodes_y[triangle_3[i] - 1] << std::endl << std::endl; 

        //x = (nodes_x[triangle_1[i] - 1] + nodes_x[triangle_2[i] - 1] + nodes_x[triangle_3[i] - 1]) / 3.0;
        //y = (nodes_y[triangle_1[i] - 1] + nodes_y[triangle_2[i] - 1] + nodes_y[triangle_3[i] - 1]) / 3.0;

        
        x1 = (nodes_x[triangle_1[i] - 1] + nodes_x[triangle_2[i] - 1]) / 2.;
        x2 = (nodes_x[triangle_2[i] - 1] + nodes_x[triangle_3[i] - 1]) / 2.;
        x3 = (nodes_x[triangle_1[i] - 1] + nodes_x[triangle_3[i] - 1]) / 2.;
        
        //std::cout << "x1 = " << x1 << " x2 = " << x2 <<" x3 = " << x3 << std::endl;

		
        y1 = (nodes_y[triangle_1[i] - 1] + nodes_y[triangle_2[i] - 1]) / 2.;
        y2 = (nodes_y[triangle_2[i] - 1] + nodes_y[triangle_3[i] - 1]) / 2.;
        y3 = (nodes_y[triangle_1[i] - 1] + nodes_y[triangle_3[i] - 1]) / 2.;
        
        //std::cout << "y1 = " << y1 << " y2 = " << y2 <<" y3 = " << y3 << std::endl;
        //std::cout << "f(x1, y1) = " << f(x1, y1) << " f(x2, y2) = " << f(x2, y2) <<" f(x3, y3) = " << f(x3, y3) << std::endl<< std::endl;
        tmp = (f(x1, y1) + f(x2, y2) + f(x3, y3))/3.;
        res += tmp;
        //std::cout << "x = " << x << " y = " << y << std::endl;
        //std::cout << "res = " << std::fixed << res << std::endl;
        //res = res + f(x, y);

    }  

    double dx = (nodes_x[N] - nodes_x[0]) / N;
    double dy = (nodes_y[(N + 1) * (N + 1) - 1] - nodes_y[0]) / N;
    //std::cout << "dx = " << dx << " dy = " << dy << std::endl;
    double S = dx * dy * 0.5;
    //std::cout << "S = " << S << std::endl;
    //std::cout << "res = " << res << std::endl;

    return res*S;
}

