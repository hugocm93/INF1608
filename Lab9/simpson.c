#include <math.h>

#include "simpson.h"

double Simpson(double a, double b, double (*f) (double x), double* v)
{
	double c = (a + b)/2;

	double fa = f(a);
	double fb = f(b);
	double fc = f(c);

	double Sab = ((b - a)/6)*(fa + 4*fc + fb);
	double Sac = ((c - a)/6)*(fa + 4*f((a + c)/2) + fc);
	double Scb = ((b - c)/6)*(fc + 4*f((c + b)/2) + fb);

	*v = Sac + Scb;

	return fabs((Sab - *v)/15);
}

double AdaptiveSimpson(double a, double b, double (*f) (double x), double tol)
{
	double v;

	if(Simpson(a, b, f, &v) <= tol)
	{
		return v;
	}
	else
	{
		double c = (a + b)/2;
		return AdaptiveSimpson(a, c, f, tol/2) + AdaptiveSimpson(c, b, f, tol/2);
	}
}
