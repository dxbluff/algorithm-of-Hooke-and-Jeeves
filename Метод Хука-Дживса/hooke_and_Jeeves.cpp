#include "hooke_and_Jeeves.h"
#include <stdio.h>
#include <math.h>
#include <iostream>
#include <iomanip> 

hooke_and_Jeeves::hooke_and_Jeeves(double(*f_)(double* x, int VARS, int n))
{
	f = f_;
};


/* given a point, look for a better one nearby, one coord at a time */
double hooke_and_Jeeves::best_nearby(double* delta, int VARS, double* point, double prevbest, int nvars)
{
	double* z = new double[VARS];
	double minf, ftmp;
	int i;
	minf = prevbest;
	for (i = 0; i < nvars; i++)
		z[i] = point[i];
	for (i = 0; i < nvars; i++) {
		z[i] = point[i] + delta[i];
		ftmp = f(z, VARS, nvars); 
		funevals++;
		if (ftmp < minf)
			minf = ftmp;
		else {
			delta[i] = 0.0 - delta[i];
			z[i] = point[i] + delta[i];
			ftmp = f(z, VARS, nvars);
			funevals++;
			if (ftmp < minf)
				minf = ftmp;
			else
				z[i] = point[i];
		}
	}
	for (i = 0; i < nvars; i++)
		point[i] = z[i];
	delete[] z;
	return (minf);
}

int hooke_and_Jeeves::hooke(int nvars, double* startpt, int VARS, double* endpt, double rho, double epsilon, int itermax)
{
	double* delta = new double[VARS];
	double newf, fbefore, steplength, tmp;
	double* xbefore = new double[VARS];
	double* newx = new double[VARS];
	int i, j, keep;
	int iters, iadj;
	for (i = 0; i < nvars; i++) {
		newx[i] = xbefore[i] = startpt[i];
		delta[i] = fabs(startpt[i] * rho);
		if (delta[i] == 0.0)
			delta[i] = rho;
	}
	iadj = 0;
	steplength = rho;
	iters = 0;
	fbefore = f(newx, VARS, nvars);
	funevals++;
	newf = fbefore;
	while ((iters < itermax) && (steplength > epsilon)) {
		iters++;
		iadj++;
		std::cout << "\nAfter " << std::setw(5) << funevals << " funevals, f(x) = " << std::setprecision(4) << std::scientific << fbefore << " at\n";
		for (j = 0; j < nvars; j++)
			std::cout << "   x[" << std::setw(2) << j << "] = " << std::setprecision(4) << std::scientific << xbefore[j] << std::endl;
		/* find best new point, one coord at a time */
		for (i = 0; i < nvars; i++) {
			newx[i] = xbefore[i];
		}
		newf = best_nearby(delta, VARS, newx, fbefore, nvars);
		/* if we made some improvements, pursue that direction */
		keep = 1;
		while ((newf < fbefore) && (keep == 1)) {
			iadj = 0;
			for (i = 0; i < nvars; i++) {
				/* firstly, arrange the sign of delta[] */
				if (newx[i] <= xbefore[i])
					delta[i] = 0.0 - fabs(delta[i]);
				else
					delta[i] = fabs(delta[i]);
				/* now, move further in this direction */
				tmp = xbefore[i];
				xbefore[i] = newx[i];
				newx[i] = newx[i] + newx[i] - tmp;
			}
			fbefore = newf;
			newf = best_nearby(delta, VARS, newx, fbefore, nvars);
			/* if the further (optimistic) move was bad.... */
			if (newf >= fbefore)
				break;
			/* make sure that the differences between the new */
			/* and the old points are due to actual */
			/* displacements; beware of roundoff errors that */
			/* might cause newf < fbefore */
			keep = 0;
			for (i = 0; i < nvars; i++) {
				keep = 1;
				if (fabs(newx[i] - xbefore[i]) >
					(0.5 * fabs(delta[i])))
					break;
				else
					keep = 0;
			}
		}
		if ((steplength >= epsilon) && (newf >= fbefore)) {
			steplength = steplength * rho;
			for (i = 0; i < nvars; i++) {
				delta[i] *= rho;
			}
		}
	}
	for (i = 0; i < nvars; i++)
		endpt[i] = xbefore[i];
	delete[] delta;
	delete[] xbefore;
	delete[] newx;
	return (iters);
}