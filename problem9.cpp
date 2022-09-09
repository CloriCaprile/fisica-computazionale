#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <cmath>
#include <algorithm>
#include <math.h>


int main ()
{
	// Set a file name
	std::string filename = "p9_results.txt";
	
	// Create an output file stream and conncect it to our file name
	std::ofstream ofile; 
	ofile.open (filename); 
	
	
	// Set some parameters for our computation
	int x_min = 0;
	int x_max = 1;
	int n_steps = 10;
	double h = (double) (x_max - x_min) / n_steps;  
	int width = 24;
	int prec = 6; 
	
	
	// create other vectors 
	std::vector<double> v(n_steps - 1);
	std::vector<double> x(n_steps - 1);
	std::vector<double> f(n_steps - 1); 
	std::vector<double> g(n_steps - 1);
	
	std::vector<double> bt(n_steps - 1);
	std::vector<double> gt(n_steps - 1);
	
	std::vector<double> vtot(n_steps + 1);
	std::vector<double> xtot(n_steps + 1);
	
	double u_0 = 0;
	double u_1 = 0;
	
	
	// fill vector x and f
	for (int i = 0; i < n_steps-1; i++)
	{
		x[i] = h + i * h;
		f[i]=100*exp(-10*x[i]); 			
	}
	
	// fill vector g

	g[0]=h*h*f[0]+u_0;
	g[n_steps-2]=h*h*f[n_steps-2]+u_1;

	for (int i=1; i < n_steps - 2; i++)
		g[i]=h*h*f[i]; 
	
		
	// fill vector bt and gt (forward substitution)
	bt[0] = 2.0;
	gt[0] = g[0];
		
	for (int i = 1; i < n_steps - 1; i++)
	{
		bt[i] = 2.0 - (1.0/ bt[i - 1]);		
		gt[i] = g[i] + ( gt[i - 1]/ bt[i - 1]);
	}
	
	
	// fill vector v (back substitution)
	v[n_steps-2] = gt[n_steps-2] / bt[n_steps-2];
	
	for (int i = n_steps - 3 ; i >= 0; i--) 
		v[i] = (gt[i] + v[i + 1]) / bt[i];			
	
	
	// fill vector x total (adding to vector x the first and last point)
	xtot[0]=x_min; 
	xtot[n_steps]=x_max;
	
	for (int i = 1; i < n_steps; i++)
		xtot[i]=x[i-1];
	
	
	// fill vector v total (adding to vector v the boundary conditions)
	vtot[0]=u_0; 
	vtot[n_steps]=u_1;
	
	for (int i = 1; i < n_steps; i++)
		vtot[i]=v[i-1];
	
	// print vector v total to file "results.txt"
	for (int i = 0; i < n_steps+1; i++)
	{	
		ofile<<std::setw(width)<<std::setprecision(prec)<<std::scientific<<xtot[i];
		ofile<<std::setw(width)<<std::setprecision(prec)<<std::scientific<<vtot[i];
		ofile<<std::endl; 
	}	
	
return 0;
}
