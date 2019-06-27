#pragma once

class hooke_and_Jeeves {
private:
	double (*f)(double* x, int VARS, int n);
	int		funevals = 0;
	double best_nearby(double* delta, int VARS, double* point, double prevbest, int nvars);
public:
	hooke_and_Jeeves(double(*f_)(double* x, int VARS, int n));
	int hooke(int nvars, double* startpt, int VARS, double* endpt, double rho, double epsilon, int itermax);
};