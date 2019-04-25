#pragma once

#define      VARS		(250)	/* max # of variables	     */
#define      RHO_BEGIN		(0.5)	/* stepsize geometric shrink */
#define      EPSMIN		(1E-6)	/* ending value of stepsize  */
#define      IMAX		(5000)	/* max # of iterations	   */

class hooke_and_Jeeves {
public:
	hooke_and_Jeeves();
	int		funevals = 0;
	double f();
	double f(double x[VARS], int n);
	double best_nearby(double delta[VARS], double point[VARS], double prevbest, int nvars);
	int hooke(int nvars, double startpt[VARS], double endpt[VARS], double rho, double epsilon, int itermax);
};