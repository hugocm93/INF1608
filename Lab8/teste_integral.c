#include <stdio.h>
#include <math.h>

#include "integral.h"

typedef enum metodo
{
  SIMPSON,
  PONTO_MEDIO
}METODO;

double f( double x )
{
  return cos(x) - 2*sin(x);
}

double f_derivada( double x )
{
  return -sin(x) - 2*cos(x);
}

double func1(double x)
{
  return x/(sqrt(x*x + 9));
}

double func2(double x)
{
  return x*x*log(x);
}

double func3(double x)
{
  return x*x*sin(x);
}

void teste(METODO m, char* funcName, double (*f) (double), double a, double b, int n)
{
  double (*func)() = m == SIMPSON ? simpson : pontomedio;

  double integral = func(f, a, b, n);
  printf("Integral de %s de %g a %g: %f\n", funcName, a, b, integral);
}

int main(void)
{

  printf("h           f'(0)          Erro\n");
  int i;
  for(i = 1; i < 13; i++)
  {
    double h = pow(10, -i);
    double fzero = derivada( f, h, 0);
    double err = fabs( fzero - f_derivada(0) );
    printf("%g    %g    %g\n", h, fzero, err);
  }
  /*O h = 1e-06 miniminiza o erro na tabela. O valor teórico é da ordem
  de 1e-05. A diferença dos valores foi de uma ordem de grandeza. A discrepância
  se deve ao fato de que o erro de máquina e de arrendondamento não está
  sendo considerado*/

  printf("\n-----\n");

  /*Para o método de simpson abaixo, não consegui seguir exatamente
  o que está no pdf. Ou seja, ao invés de usar a forma alternativa,
  usei a forma 5.22 presente no livro-texto do Sauer*/

  printf("Simpson\n");
  teste(SIMPSON, "func1", func1, 0, 4, 16);
  teste(SIMPSON, "func2", func2, 1, 3, 16);
  teste(SIMPSON, "func3", func3, 0, M_PI, 16);

  teste(SIMPSON, "func1", func1, 0, 4, 32);
  teste(SIMPSON, "func2", func2, 1, 3, 32);
  teste(SIMPSON, "func3", func3, 0, M_PI, 32);

  printf("Ponto medio\n");
  teste(PONTO_MEDIO, "func1", func1, 0, 4, 16);
  teste(PONTO_MEDIO, "func2", func2, 1, 3, 16);
  teste(PONTO_MEDIO, "func3", func3, 0, M_PI, 16);

  teste(PONTO_MEDIO, "func1", func1, 0, 4, 32);
  teste(PONTO_MEDIO, "func2", func2, 1, 3, 32);
  teste(PONTO_MEDIO, "func3", func3, 0, M_PI, 32);



  return 0;
}
