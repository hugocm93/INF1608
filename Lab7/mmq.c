#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "mmq.h"
#include "gauss.h"

double* mmq (int m, int n, double** A, double* b)
{
  Matriz transposta = mat_cria(n, m);
  mat_transposta(m, n, A, transposta);

  Matriz matAux = mat_cria(n, n);
  mat_multm(n, m, n, transposta, A, matAux);

  double* vecAux = (double*)malloc(sizeof(double)*n);
  mat_multv(n, m, transposta, b, vecAux);

  double* x = (double*)malloc(sizeof(double)*n);
  gauss(n, matAux, vecAux, x);

  mat_libera(n, transposta);
  mat_libera(n, matAux);
  free(vecAux);

  return x;
}

double norma2 (int m, int n, double** A, double* b, double* x)
{
  double* Ax = (double*)malloc(sizeof(double)*m);
  mat_multv(m, n, A, x, Ax);

  double* r = (double*)malloc(sizeof(double)*m);
  int i;
  for(i = 0; i < m; i++)
  {
    r[i] = b[i] - Ax[i];
  }

  double erro = 0;
  for(i = 0; i < m; i++)
  {
    erro += r[i]*r[i];
  }

  free(Ax);
  free(r);

  return sqrt(erro);
}
