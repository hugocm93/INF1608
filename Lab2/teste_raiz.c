#include <stdio.h>
#include <math.h>
#include "raiz.h"

double v( double m );
double g( double x );


int main()
{
  printf( "Bisseção:\nRaiz de v(m): %.10g\n", bissecao( 50, 100, 6, &v ) );

  printf( "Raiz de sin(x): %.10g\n", bissecao( 3.14/2, 4, 6,  &sin ) );

  printf( "Ponto Fixo: \nRaiz de f(x): %.10g\n", pontofixo( 5, 0.0005, &g ) );

  return 0;
}

double v( double m )
{
  return 35 - ( ( 9.8*m )/15 )*( 1 - exp( - ( 15*9 )/m ) ) ;
}

double g( double x )
{
  return ( 2.5 / x ) + 1.8;
}
