#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "poly.h"

unsigned fatorial(unsigned n)
{
    if (n == 1)
        return 1;
    else
        return n * fatorial(n - 1);
}

int main(void)
{
  int n = 6;
  double a = 0, b = M_PI/2;
  double erro =  pow((b-a)/2, n) / (pow(2, n-1) * fatorial(n));

  Sample* s = Chebyshev(n, a, b, &cos);
  double* B = NewtonCompute(s);

  double x;
  for(x = -2*M_PI; x < 2*M_PI; x += 0.1)
  {
    double aprox = NewtonEval(s, B, x);
    double cosx = cos(x);

    printf("x: %.4g, cos(x): %.4g, aprox(x):%.4g, ",
           x, cosx, aprox);

    if(fabs(cosx - aprox) <= erro)
    {
      printf("Erro esperado\n");
    }
    else
    {
      printf("Erro alto %.16g - %.16g\n", fabs(cosx - aprox), erro);
    }
  }

  free(B);
  libera(s);

  return 0;
}
