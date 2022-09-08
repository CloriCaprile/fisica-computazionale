#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <iomanip>
#include <math.h> 
#include <chrono>
#include <numeric>
// #include <armadillo>
#include "useful.hpp"

int main(){

    int n = 1000;
    int n_runs = 10;
    double x_min = 0, x_max = 1, h;

    h = (x_max - x_min)/n;
    std::vector<double> x(n+1), u(n+1), a(n-2, -1), b(n-1, 2), c(n-2, -1), g(n-1), v_generic(n-1), v_specific(n-1), time_generic(n_runs), time_specific(n_runs);

    x[0] = x_min;
    u[0] = 0;
    for (int i=0; i < n; i++){
        x[i+1] = x[i] + h;
        u[i+1] = (double) 1 - ( 1- exp(-10) )*x[i+1] - exp(-10*x[i+1]);
        if (i < n-1){
            g[i] = h*h*100*exp(-10*x[i+1]);
        }
    }
    g[0] += u[0];
    g[n-2] += u[n];

    for (int i=0; i<n_runs; i++){
        auto t1_generic = std::chrono::high_resolution_clock::now();
        v_generic = thomas_algo(a, b, c, g);
        auto t2_generic = std::chrono::high_resolution_clock::now();

        auto t1_specific = std::chrono::high_resolution_clock::now();
        v_specific = thomas_algo(a, b, c, g);
        auto t2_specific = std::chrono::high_resolution_clock::now();

        time_generic[i] = std::chrono::duration<double>(t2_generic - t1_generic).count();
        time_specific[i] = std::chrono::duration<double>(t2_specific - t1_specific).count();

    }

    double duration_generic = std::accumulate(time_generic.begin(), time_generic.end(), 0.0)/time_generic.size();
    double duration_specific = std::accumulate(time_specific.begin(), time_specific.end(), 0.0)/time_specific.size();

    std::cout   << "Time spent by the generic algorithm: " 
                << duration_generic 
                <<"\nTime spent by the specific algorithm: " 
                << duration_specific
                <<std::endl;




    return 0;
}