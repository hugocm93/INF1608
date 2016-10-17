#ifndef POLY
#define POLY

typedef struct sample Sample;

Sample* Chebyshev(int n, double a, double b, double (*f) (double x));

double* NewtonCompute(Sample* s);

double NewtonEval(Sample* s, double* b, double x);

void libera(Sample* s);

#endif
