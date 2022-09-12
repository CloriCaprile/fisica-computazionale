#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <iomanip>
#include <math.h> 
#include <chrono>
#include <numeric>
#include "useful.hpp"

int main(){

    // for each choice of n_steps we sample n_runs timings for each algorithm
    int n_runs = 1000;
    const int arr[] = {1e1, 1e2, 1e3, 1e4, 1e5, 1e6};
    std::vector<int> n_vec (arr, arr + sizeof(arr) / sizeof(arr[0]) );
    int x_min = 0, x_max = 1;
    double  h;

    // Set a file name
    std::string filename_g = "p10_generic.txt", filename_s = "p10_specific.txt";
    
    // Create an output file stream and conncect it to our file name
    std::ofstream ofile_g, ofile_s; 
    ofile_g.open (filename_g);
    ofile_s.open (filename_s); 

    for (int n : n_vec){

        std::cout << "Timing for n = " <<n << "\t\r" << std::flush;

        // prepare the inputs
        h = ((double) x_max - x_min)/n;
        std::vector<double> x(n+1), u(n+1), a(n-2, -1), b(n-1, 2), c(n-2, -1), g(n-1), v_temp(n-1), time_generic(n_runs), time_specific(n_runs);

        x[0] = x_min;
        u[0] = 0;
        for (int i=0; i < n; i++){
            x[i+1] = x[i] + h;
            u[i+1] = (double) 1 - ( 1 - exp(-10) )*x[i+1] - exp(-10*x[i+1]);
            if (i < n-1){
                g[i] = h*h*100*exp(-10*x[i+1]);
            }
        }
        g[0] += u[0];
        g[n-2] += u[n];

        // timing  of the algorithms
        for (int i=0; i<n_runs; i++){
            auto t1_generic = std::chrono::high_resolution_clock::now();
            v_temp = thomas_algo(a, b, c, g);
            auto t2_generic = std::chrono::high_resolution_clock::now();

            auto t1_specific = std::chrono::high_resolution_clock::now();
            v_temp = specific_algo(g);
            auto t2_specific = std::chrono::high_resolution_clock::now();

            time_generic[i] = std::chrono::duration<double>(t2_generic - t1_generic).count();
            time_specific[i] = std::chrono::duration<double>(t2_specific - t1_specific).count();

        }

        double duration_generic = std::accumulate(time_generic.begin(), time_generic.end(), 0.0)/time_generic.size();
        double duration_specific = std::accumulate(time_specific.begin(), time_specific.end(), 0.0)/time_specific.size();

        double var_generic = 0, var_specific = 0;
        for (int i = 0; i < n_runs; i++){
            var_generic += (time_generic[i] - duration_generic)*(time_generic[i] - duration_generic);
            var_specific += (time_specific[i] - duration_specific)*(time_specific[i] - duration_specific);
            // pow(x, 2) is slower than x*x
        }

        var_generic /= n_runs-1;
        var_specific /= n_runs-1;

        double stddev_generic = sqrt(var_generic);
        double stddev_specific = sqrt(var_specific);

        ofile_g << scientific_format(duration_generic, 24, 6) << scientific_format(stddev_generic, 24, 6) << std::endl;
        ofile_s << scientific_format(duration_specific, 24, 6) << scientific_format(stddev_specific, 24, 6) <<std::endl;
        

    }

    std::cout << "Done! Check out the output files" << std::endl;

    ofile_g.close();
    ofile_s.close();



    return 0;
}