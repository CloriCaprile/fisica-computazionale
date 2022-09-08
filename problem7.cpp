#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <iomanip>
#include <math.h> 
#include "useful.hpp"


int main(){
    int n=1000; //number of steps
    double x_min=0;
    double x_max=1;
    int width=16;
    int prec=4;
    double h = (x_max - x_min) / n;
    std::cout <<"h ="<< h << "\n";

    //Initialize x and v with a length 
    std::vector<double> x(n+1); 
    std::vector<double> u(n+1);
    std::vector<double> f(n-1);
    std::vector<double> a(n-2,-1);
    std::vector<double> b(n-1,2);
    std::vector<double> c(n-2,-1);
    std::vector<double> g(n-1);
    std::vector<double> b_tilde(n-1);
    std::vector<double> g_tilde(n-1);
    std::vector<double> v_star(n+1);



    // Set a filename 
    std::string filename0 = "data/u"+ std::to_string(n)+ ".txt";
    // Create and open the output file. Or, technically, create 
    // an "output file stream" (type std::ofstream) and connect it to our filename.
    std::ofstream ofile0;
    ofile0.open(filename0);

    // fill x and u vectors, (print them), and store them in a file "u.txt" 
    x[0]=x_min;
    for(int i = 0 ; i <= n; i++){
        x[i] = x_min +  i*h;
        u[i] =(double) 1 - ( 1- exp(-10) )*x[i] - exp(-10*x[i]);
        if (i <= n-1){
            f[i]=100*exp(-10*x[i]);
            if(i!=0 || i!=n-2){
                g[i]= h*h*f[i];
            }
            else if(i=0){
                g[i]= h*h*f[i] + u[0];
            } else if(i=n-2){
                g[i]= h*h*f[i] + u[n];
            }
        }
        // std::cout<< i << "," << f[i] << "," << g[i] << "\n";
        //std::cout << i << scientific_format(x[i], width, prec ) << " , " << scientific_format(u[i], width, prec )<<  "\n";
        ofile0 << scientific_format(x[i], width, prec ) << scientific_format(u[i], width, prec )<<  std::endl;
    }
    ofile0.close();


    // declare v and fill it with thomas algorithm by calling the function
    std::vector<double> v(n-1);
    v=thomas_algo(a,b,c,g);

    // define the complete solution v_star
    v_star[0]=u[0];
    for(int i=0; i<= n-1; i++){
        v_star[i+1]=v[i];
    }
    v_star[n]=(u[n]);

    
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

    // save in file v(x)
    for(int i=0; i<=n; i++){
    ofile << scientific_format(x[i], width, prec ) << scientific_format(v_star[i], width, prec )<<  std::endl;
    }

    // save in file error and relative error
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