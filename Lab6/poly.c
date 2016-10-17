#include <math.h>
#include <stdlib.h>

#include "poly.h"

struct sample {
  int n;      /* número de amostras */
  double* x;  /* valores x das amostras */
  double* y;  /* valores y das amostras */
};


/* Métodos auxiliares internos */
Sample* sample_cria(int n);
double DDN(int i, int j, Sample* s);
double produtorio(Sample* s, double x, int i);

Sample* sample_cria(int n)
{
  Sample* sample = (Sample*)malloc(sizeof(Sample));
  sample->x = (double*)malloc(sizeof(double)*n);
  sample->y = (double*)malloc(sizeof(double)*n);
  sample->n = n;

  return sample;
}


Sample* Chebyshev(int n, double a, double b, double (*f) (double x))
{
  Sample* sample = sample_cria(n);

  int i, B;
  for(i = 0, B = 1; i < n; i++, B+=2)
  {
    sample->x[i] = ((b-a)/2)*cos((B*M_PI)/(2*n));
    sample->y[i] = f(sample->x[i]);
  }

  return sample;
}


double* NewtonCompute(Sample* s)
{
  double* b = (double*)malloc(sizeof(double)*(s->n));

  int i;
  for(i = 0; i < s->n; i++)
  {
    //TODO: Usar iteração ao invés de recursão
    b[i] = DDN(0, i, s);
  }

  return b;
}


double DDN(int i, int j, Sample* s)
{
  if(i == j)
  {
    return s->y[i];
  }
  else
  {
    return (DDN(i+1, j, s) - DDN(i, j-1, s))/(s->x[j] - s->x[i]);
  }
}


double NewtonEval(Sample* s, double* b, double x)
{
  //TODO: ajustar intervalo

  int m = 0, n = 0;
  if(x > M_PI/2)
  {
    while(x > M_PI/2)
    {
      x -= M_PI/2;
      m++;
    }
  }
  else if( x < 0)
  {
    while(x < 0)
    {
      x += M_PI/2;
      n++;
    }
  }

  int i;
  double p = 0;

  for(i = 0; i < s->n; i++)
  {
    p += b[i]*produtorio(s, x, i);
  }

  if( m == 0)
  {
    return n%2 == 0 ? p : -p;
  }
  else
  {
    return m%2 == 0 ? -p : p;
  }
}


double produtorio(Sample* s, double x, int i)
{
  int j;
  double acum = 1;

  for(j = 0; j < i; j++)
  {
    acum *= x - s->x[j];
  }

  return acum;
}


void libera(Sample* s)
{
  free(s->x);
  free(s->y);
  free(s);
}
