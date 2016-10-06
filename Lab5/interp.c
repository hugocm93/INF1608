#include <math.h>
#include <stdlib.h>

#include "interp.h"

double** fatoracao (int n, double** A)
{
  Matriz P = mat_cria(n, n);
  mat_preenche_ID(n, P);

  int i, j, k, p;
  for(j = 0; j < n-1; j++)
  {
    //Pivotamento
    p = j;
    for(k = j+1; k < n; k++)
    {
      if( fabs(A[k][j]) > fabs(A[p][j]))
      {
        p = k;
      }
    }

    for(k = 0; k < n; k++)
    {
      double swap_temp = A[j][k];
      A[j][k] = A[p][k];
      A[p][k] = swap_temp;

      swap_temp = P[p][k];
      P[p][k] = P[j][k];
      P[j][k] = swap_temp;
    }
    //end pivotamento

    //LU
    for(i = j+1; i < n; i++)
    {
      double f = A[i][j]/A[j][j];
      for(k = j; k < n; k++)
      {
        A[i][k] -= A[j][k]*f;
      }
      A[i][j] = f;
    }
    //end LU
  }
  return P;
}


double* substituicao (int n, double** A, double** P, double* B)
{
  //Ajuste no vetor
  double* b = (double*)malloc(sizeof(double)*n);
  mat_multv( n, n, P, B, b );

  int i, j;
  for(j = 0; j < n-1; j++)
  {
    for(i = j+1; i < n; i++)
    {
      double f = A[i][j];
      b[i] -= b[j]*f;
    }
  }
  //end Ajuste no vetor

  //Resolução
  double* x = (double*)malloc(sizeof(double)*n);
  mat_zerav(n, x);

  for(i = n-1; i >= 0; i--)
  {
    double acum = 0;
    for(j = n-1; j > i; j--)
    {
      acum += A[i][j]*x[j];
    }
    x[i] = (b[i]-acum)/A[i][j];
  }
  free(b);
  //end resolução
  return x;
}


double* interpola (int n, double* px, double* py)
{
  return NULL;
}


double avalia (int n, double* c, double x)
{
  return 0;
}


double lagrange (int n, double* px, double* py, double x)
{
  int i, j;
  double Li, y = 0;
  for( i = 0; i < n; i++)
  {
    Li = 1;
    for( j = 0; j < n; j++)
    {
      if(j != i) Li *= (x - px[j]) / (px[i] - px[j]);
    }
    y += py[i]*Li;
  }
  return y;
}
