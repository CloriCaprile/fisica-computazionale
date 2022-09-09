#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <iomanip>
#include <math.h> 
#include "useful.hpp"


int main(){
    int n=100; //number of steps
    double x_min=0;
    double x_max=1;
    double u_0=0;
    double u_n=0;
    int width=30;
    int prec=10;
    double h = (x_max - x_min) / n;
    std::cout <<"h ="<< h << "\n";

    //Initialize vectors
    std::vector<double> x(n+1), u(n+1), f(n-1), a(n-2,-1), b(n-1,2), 
                        c(n-2,-1), g(n-1), b_tilde(n-1), g_tilde(n-1), v_star(n+1);

    //Boundary values
    x[0] = x_min;
    u[0] = u_0;

    // Set a filename 
    std::string filename0 = "data/u"+ std::to_string(n)+ ".txt";
    // Create and open the output file. Or, technically, create 
    // an "output file stream" (type std::ofstream) and connect it to our filename.
    std::ofstream ofile0;
    ofile0.open(filename0);

    
    

    // fill x, u and g vectors, (print them), and store them in some txt files
    for (int i=0; i < n; i++){
        x[i+1] = x[i] + h;
        u[i+1] = (double) 1 - ( 1- exp(-10) )*x[i+1] - exp(-10*x[i+1]);
        if (i < n-1){
            g[i] = h*h*100*exp(-10*x[i+1]);
        }
        // std::cout<< i << "," << f[i] << "," << g[i] << "\n";
        //std::cout << i << scientific_format(x[i], width, prec ) << " , " << scientific_format(u[i], width, prec )<<  "\n";
        ofile0 << scientific_format(x[i], width, prec ) << scientific_format(u[i], width, prec )<<  std::endl;

    }
    //close file
    ofile0.close();

    //set values and correct g
    u[n] = u_n;
    g[0] += u[0];
    g[n-2] += u[n];



    // declare v and fill it with thomas algorithm by calling the function
    std::vector<double> v(n-1);
    v = thomas_algo(a,b,c,g);
    

    // define the complete solution v_star
    v_star[0]=u[0];
    for(int i=0; i<= n-2; i++){
        v_star[i+1]=v[i];
    }
    v_star[n]=u[n];

    
    // Set some filenames
    std::string filename = "data/v"+ std::to_string(n)+ ".txt";
    std::string filename2 = "data/error"+ std::to_string(n) +".txt";
    std::string filename3 = "data/rel_error"+ std::to_string(n) +".txt";

    // Create and open the output files
    std::ofstream ofile;
    std::ofstream ofile2;
    std::ofstream ofile3;
    ofile.open(filename);
    ofile2.open(filename2);
    ofile3.open(filename3);

    // save v to file
    for(int i=0; i<=n; i++){
    ofile << scientific_format(x[i], width, prec ) << scientific_format(v_star[i], width, prec )<<  std::endl;
    }

    // save delta and epsilon to file
    for(int i=0; i<=n-2; i++){
    ofile2 << scientific_format(x[i+1], width, prec ) << scientific_format( fabs((long double) u[i+1]-v[i]), width, prec )<<  std::endl;
    ofile3 << scientific_format(x[i+1], width, prec ) << scientific_format( fabs(((long double) u[i+1]-v[i])/u[i+1]), width, prec )<<  std::endl;
    }
    // Close the output file
    ofile.close();
    ofile2.close();
    ofile3.close();


    return 0;
}