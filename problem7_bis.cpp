
#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <cmath>
#include <algorithm>
#include <math.h>

#include <fstream>

using namespace std;

int main()
{

	// Set some parameters for our computation
	int x_min = 0;
	int x_max = 1;
	int n_steps = 10;
	double h = (double) (x_max - x_min) / n_steps;  
	ofstream fout("result.txt");
	

	// Create vectors for the superdiagonal (a), main diagonal (b) and subdiagonal (c)
	std::vector<float> a(n_steps-2);
	std::vector<float> b(n_steps-1);
	std::vector<float> c(n_steps-2);
	
	// Assign the elements of the three vectors using a loop.	
	for (int i = 0; i < n_steps - 2 ; i++)
	{	
		a[i] = -1;
		c[i] = -1;
	}
	
	for (int i = 0; i < n_steps - 1; i++)
		b[i] = 2;
				
	
	// create other vectors 
	std::vector<double> v(n_steps - 1);
	std::vector<double> x(n_steps - 1);
	std::vector<double> f(n_steps - 1); 
	std::vector<double> g(n_steps - 1);
	
	std::vector<double> bt(n_steps - 1);
	std::vector<double> gt(n_steps - 1);
	
	std::vector<double> vtot(n_steps + 1);
	
	double u_0 = 0;
	double u_1 = 0;
	
	
	// fill vector x and f
	for (int i = 0; i < n_steps-1; i++)
	{
		x[i] = h + i * h;
		f[i]=100*exp(-10*x[i]); 			
	}
	
	for (int i=0; i<n_steps-1; i++)
		std::cout <<x[i]<<'\n'; 
	
	
	
	// fill vector g

	g[0]=h*h*f[0]+u_0;
	g[n_steps-2]=h*h*f[n_steps-2]+u_1;

	for (int i=1; i < n_steps - 2; i++)
		g[i]=h*h*f[i]; 
	
		
	// fill vector bt and gt (forward substitution)
	bt[0] = b[0];
	gt[0] = g[0];
		
	for (int i = 1; i < n_steps - 1; i++)
	{
		bt[i] = b[i] - ((a[i - 1] * c[i - 1]) / bt[i - 1]);		//changed a index from [i] to [i-1] to match the lenght of vector a
		gt[i] = g[i] - ((a[i - 1] * gt[i - 1]) / bt[i - 1]);
	}
	
	
	// fill vector v (back substitution)
	v[n_steps-2] = gt[n_steps-2] / bt[n_steps-2];
	
	for (int i = n_steps - 2 ; i >= 0; i--) 
		v[i] = (gt[i] - (c[i] * v[i + 1]) )/ bt[i];			
	
	
	// fill vector v total (adding to vector v the boundary conditions)
	vtot[0]=u_0; 
	vtot[n_steps]=u_1;
	
	for (int i = 1; i < n_steps; i++)
		vtot[i]=v[i-1];
	
	// print vector v total to file "results.txt"
	for (int i = 0; i < n_steps+1; i++)
		fout <<vtot[i] <<'\n'; 

return 0;
}
