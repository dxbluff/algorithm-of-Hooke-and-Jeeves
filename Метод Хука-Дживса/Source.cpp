#include "hooke_and_Jeeves.h"
#include <iostream>
#include <iomanip> 


int main()
{
	double	   startpt[VARS], endpt[VARS];
	int		   nvars, itermax;
	double	   rho, epsilon;
	int		   i, jj;

	/* starting guess for rosenbrock test function */
	nvars = 2;
	startpt[0] = -1.2;
	startpt[1] = 1.0;
	

	itermax = IMAX;
	rho = RHO_BEGIN;
	epsilon = EPSMIN;


	hooke_and_Jeeves algh;


	jj = algh.hooke(nvars, startpt, endpt, rho, epsilon, itermax);

     //	printf("\n\n\nHOOKE USED %d ITERATIONS, AND RETURNED\n", jj);

	std::cout << "\n\n";
	std::cout << "HOOKE USED " << jj << " ITERATORS, AND RETURNED" << std::endl;


	for (i = 0; i < nvars; i++)
		std::cout << "x[" << std::setw(3) << i << "] = " << std::setprecision(7) << std::scientific << endpt[i] << std::endl;
}