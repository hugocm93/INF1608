#include <math.h>
#include <stdlib.h>

#include "interp.h"

double** fatoracao (int n, double** A)
{

  Matriz P = mat_cria(n, n);
  mat_preenche_ID(n, P);

  double f, swap_temp;
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
      swap_temp = A[j][k];
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
      f = A[i][j]/A[j][j];
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

double* substituicao (int n, double** A, double** P, double* b)
{
  double f;

  Matriz B = mat_cria(1,n);
  Matriz PB = mat_cria(1,n);

  int i, j;
  for(i=0; i<n; i++)
  {
    B[0][i] = b[i];
  }

  mat_multv( n, n, P, &B[0][0], &PB[0][0] );

  for(i=0; i<n; i++)
  {
    b[i] = PB[0][i];
  }

  mat_libera(1, B);
  mat_libera(1, PB);

  double* x = (double*)malloc(sizeof(double)*n);
  mat_zerav(n, x);

  for(j = 0; j < n-1; j++)
  {
    for(i = j+1; i < n; i++)
    {
      f = A[i][j];
      b[i] -= b[j]*f;
      A[i][j] = 0;
    }
  }

  //Resolução
  for(i = n-1; i >= 0; i--)
  {
    double acum = 0;
    for(j = n-1; j > i; j--)
    {
      acum += A[i][j]*x[j];
    }
    x[i] = (b[i]-acum)/A[i][j];
  }
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
 return 0;
}
