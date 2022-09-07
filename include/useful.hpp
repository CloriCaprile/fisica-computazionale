
// include guard
#ifndef __useful_hpp__  
#define __useful_hpp__

// include headers
#include <string>
#include <vector>
#include <sstream>
#include <iomanip>

// Return a string with a double in scientific notation
std::string scientific_format(double d, const int& width, const int& prec);


// Return a string with a vector<double> in scientific notation
std::string scientific_format(const std::vector<double>& v, const int& width, const int& prec);

// Return solution v to the problem A*v=g, with Thomas' algorithm.
// Input vectors: a subdiagonal, b diagonal, c superdiagonal of matrix A.  
std::vector<double> thomas_algo(std::vector<double>& a, std::vector<double>& b, std::vector<double>& c, std::vector<double>& g);

#endif  // end of include guard __useful_hpp__