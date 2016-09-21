#include "raiz2.h"
#include <math.h>
#include <stdio.h>

double f( double x );
double fl( double x );

int main()
{
  double r1 = 0 ;
  double r2 = 0 ;
  printf("NR  -> nIterações: %d Raiz: %.6f \n", NR( 1.14, 6, &f, &fl, &r1 ), r1 );
  printf("IQI -> nIterações: %d Raiz: %.6f \n", IQI( 1.13, 1.14, 1.16, 6, &f, &r2 ), r2 );
  printf("\n");

  r1 = 0 ;
  r2 = 0 ;
  printf("NR  -> nIterações: %d Raiz: %.6f \n", NR( 3, 6, &f, &fl, &r1 ), r1 );
  printf("IQI -> nIterações: %d Raiz: %.6f \n", IQI( 1, 3, 5, 6, &f, &r2 ), r2 );
  printf("\n");

  r1 = 0 ;
  r2 = 0 ;
  printf("NR  -> nIterações: %d Raiz: %.6f \n", NR( 1000, 6, &f, &fl, &r1 ), r1 );
  printf("IQI -> nIterações: %d Raiz: %.6f \n", IQI( 900, 1000, 1200, 6, &f, &r2 ), r2 );
  printf("\n");

  r1 = 0 ;
  r2 = 0 ;
  printf("NR  -> nIterações: %d Raiz: %.6f \n", NR( 0, 6, &f, &fl, &r1 ), r1 );
  printf("IQI -> nIterações: %d Raiz: %.6f \n", IQI( -2, 0, 2, 6, &f, &r2 ), r2 );
  printf("\n");

  return 0;
}


double f( double x)
{
  return cos( x ) - x*x*x + x;
}


double fl( double x)
{
  return -sin( x ) - 3*x*x + 1;
}
