#include "interp.h"
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
  double px[] = {-5, -4, -3, -2, -1, 0, 1, 2, 3, 4, 5};
  double py[] = {5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 42};
  int n = 11;

  double x[] = {-1, -0.8, -0.6, -0.4, -0.2, 0, 0.2, 0.4, 0.6, 0.8, 1};
  int nx = 11;

  int i;
  for(i = 0; i < nx; i++)
  {
    printf("x:%.3g y:%.3g \n", x[i], lagrange(n, px, py, x[i]) );
  }

  return 0;
}
