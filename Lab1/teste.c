#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "fcos.h"

float r( float x);

int main( void )
{
  int i=0, j=0;
  for( float x = 0; x <= PI; x += 0.01 )
  {
    if( fabs( fcos( x ) - cos( x ) ) > fabs( r( x ) ) )
    {
      printf( "False %.16g fabs: %.16g r: %.16g\n", fabs( fcos( x ) - cos( x ) ), fabs( r( x ) ), x );
      i++;
    }
    else
    {
      printf( "True %.16g fabs: %.16g r: %.16g\n", fabs( fcos( x ) - cos( x ) ), fabs( r( x ) ), x );
      j++;
    }
  }
  printf("%d Ok, %d not OK\n", j, i );

  return 0;
}

float r( float x)
{
  return pow( ( x - PI/2 ), 5 ) / 120;
}

/*
  Foi feito um teste para valores de x variando de 0 à Pi de 0.01 em 0.01. 315 casos foram observados e desses, 5 resultados não foram iguais ao esperado. Para valores de x próximos de Pi/2, o erro vai para 0 mais rápido do que a diferença entre as funcões fcos e cos(Math). Acredito que isso aconteça pois ambas as funções fcos e cos são aproximações da função teórica cos, porém a cos(Math) tem uma precisão maior do que a fcos.
*/
