#ifndef INTERP
#define INTERP

#include "matriz.h"

double** fatoracao (int n, double** A);

double* substituicao (int n, double** A, double** P, double* B);

double* interpola (int n, double* px, double* py);

double avalia (int n, double* c, double x);

double lagrange (int n, double* px, double* py, double x);

#endif
