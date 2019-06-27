#include "hooke_and_Jeeves.h"
#include <iostream>
#include <iomanip> 

/* Rosenbrocks classic parabolic valley ("banana") function */
double f(double* x, int VARS, int n)
{
	double a, b, c;
	//funevals++;
	a = x[0];
	b = x[1];
	c = 100.0 * (b - (a * a)) * (b - (a * a));
	return (c + ((1.0 - a) * (1.0 - a)));
}

int main()
{
	int VARS = 250;
	double RHO_BEGIN = 0.5;
	double EPSMIN = 1E-6;
	int IMAX = 5000;

	double* startpt = new double[VARS];
	double* endpt = new double[VARS];
	int nvars, itermax;
	double rho, epsilon;
	int i, jj;

	/* starting guess for rosenbrock test function */
	nvars = 2;
	startpt[0] = -1.2;
	startpt[1] = 1.0;

	itermax = IMAX;
	rho = RHO_BEGIN;
	epsilon = EPSMIN;

	hooke_and_Jeeves algh(f);

	jj = algh.hooke(nvars, startpt, VARS, endpt, rho, epsilon, itermax);

	std::cout << "\n\nHOOKE USED " << jj << " ITERATORS, AND RETURNED" << std::endl;

	for (i = 0; i < nvars; i++)
		std::cout << "x[" << std::setw(3) << i << "] = " << std::setprecision(7) << std::scientific << endpt[i] << std::endl;

	delete[] startpt;
	delete[] endpt;
}