#include <stdio.h>

#include "integral.h"

double derivada(double (*f) (double x), double h, double x)
{
  return (f(x + h) - f(x - h))/(2*h);
}

double simpson(double (*f) (double), double a, double b, int n)
{
  double h = (b - a)/n, soma = 0;
  double s1 = 0, s2 = 0;
  if(n%2 == 0)
  {
    int i;
    for(i = 1; i <= n-1; i++)
    {
      if(i%2==0)
      {
        s1=s1+f(a+i*h);
      }
      else
      {
        s2=s2+f(a+i*h);
      }
    }
    soma = h/3*(f(a)+f(b)+4*s2+2*s1);
  }
  else
  {
    printf("n é ímpar\n");
  }

  return soma;
}

double pontomedio(double (*f) (double), double a, double b, int n)
{
  double h = (b - a)/n;
  double s1 = 0;

  int i;
  for(i = 1; i <= n; i++)
  {
    s1 = s1 + f(a + i*h);
  }

  return h*s1;
}
