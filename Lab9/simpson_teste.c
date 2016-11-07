#include <stdio.h>
#include <math.h>

#include "simpson.h"

double func1(double x)
{
	return x/(sqrt(x*x + 9));
}


double func2(double x)
{
	return exp((-x*x)/2);
}


double func3(double x)
{
	return exp(-x*x);
}


int main(void)
{
	double tol = 0.5 * pow(10, -7);

	double r1 = AdaptiveSimpson(0, 1, func1, tol);

	double r2 = 1/(sqrt(2*M_PI))*AdaptiveSimpson(-1, 1, func2, tol);

	double r3 = 2/(sqrt(M_PI))*AdaptiveSimpson(0, 3, func3, tol);

	printf("func1: %.7f  func2: %.7f func3: %.7f\n", r1, r2, r3);

	return 0;
}
