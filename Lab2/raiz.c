#include "raiz.h"
#include <stdlib.h>
#include <math.h>

double bissecao( double a, double b, int p, double ( *f ) ( double x ) )
{
  double erro = 0.5 * pow( 10 , -p );
  double c = 0;
  double fc = 0;
  double fa = f( a );

  do
  {
      c  = ( a + b )/2;
      fc = f( c );

      if( fa*fc < 0 )
      {
        b = c;
      }
      else
      {
        a  = c;
        fa = fc;
      }
  }while( fabs( fc ) >= erro );

  return c;
}

double pontofixo( double x0, double epsilon, double ( *g ) ( double x ) )
{
  while( fabs( g( x0 ) - x0 ) > epsilon )
  {
    x0 = g( x0 );
  }
  return x0;
}
