#pragma once

class hooke_and_Jeeves {
public:
	hooke_and_Jeeves();
	int		funevals = 0;
	double f();
	double f(double* x, int VARS, int n);
	double best_nearby(double* delta, int VARS, double* point, double prevbest, int nvars);
	int hooke(int nvars, double* startpt, int VARS, double* endpt, double rho, double epsilon, int itermax);
};