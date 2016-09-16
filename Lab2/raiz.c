#include "raiz.h"
#include <stdlib.h>
#include <math.h>

double bissecao( double a, double b, int p, double ( *f ) ( double x ) )
{
  double erro = 0.5 * pow( 10 , -p );
  int nIteracoes = log2( (b - a)/erro );
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
      if( !nIteracoes-- )
      {
        //Se não achar raíz
        return NAN;
      }
  }while( fabs( fc ) >= erro );

  return c;
}

double pontofixo( double x0, double epsilon, double ( *g ) ( double x ) )
{
  double xMenosDois = 0;
  double xMenosUm = x0;

  while( fabs( g( x0 ) - x0 ) > epsilon )
  {
    xMenosDois = xMenosUm;
    xMenosUm = x0;
    x0 = g( x0 );

    if( x0 == xMenosDois)
    {
      //Se não achar raíz
      return NAN;
    }
  }
  return x0;
}
