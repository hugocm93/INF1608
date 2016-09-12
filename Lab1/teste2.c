#include <stdio.h>
#include <math.h>

float r( float x);

int main( void )
{
  printf("%.16g\n", 9.4 - 9 - 0.4);
  double erro = 1/pow(2, 52) + 1/pow(2, 53);
  printf("%.16g\n", erro);
  return 0;
}
