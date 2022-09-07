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
    //std::string filename = "u.txt";
    // Create and open the output file. Or, technically, create 
    // an "output file stream" (type std::ofstream) and connect it to our filename.
    //std::ofstream ofile;
    //ofile.open(filename);

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
                g[i]= h*h*f[i] + u[i-1];
            } else if(i=n-2){
                g[i]= h*h*f[i] + u[i+1];
            }
        }
        // std::cout<< i << "," << f[i] << "," << g[i] << "\n";
        //std::cout << i << scientific_format(x[i], width, prec ) << " , " << scientific_format(u[i], width, prec )<<  "\n";
        //ofile << scientific_format(x[i], width, prec ) << scientific_format(u[i], width, prec )<<  std::endl;
    }

    std::vector<double> v(n-1);
    v=thomas_algo(a,b,c,g);
    v_star[0]=u[0];
    for(int i=0; i<= n-1; i++){
        v_star[i+1]=v[i];

    }
    v_star[n]=(u[n]);


    
    // Set a filename 
    std::string filename = "v1000.txt";
    // Create and open the output file. Or, technically, create 
    // an "output file stream" (type std::ofstream) and connect it to our filename.
    std::ofstream ofile;
    ofile.open(filename);

    for(int i=0; i<=n; i++){
    //std::cout << i << scientific_format(x[i], width, prec ) << " , " << scientific_format(u[i], width, prec )<<  "\n";
    ofile << scientific_format(x[i], width, prec ) << scientific_format(v[i], width, prec )<<  std::endl;
    }

    // Close the output file
    ofile.close();


    return 0;
}



