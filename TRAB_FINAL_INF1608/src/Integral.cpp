#include <cassert>

#include "Integral.h"

double Integral::simpson( std::function< double ( double ) >& function, double a, double b, double h )
{
    double sum = 0;
    double s1 = 0, s2 = 0;

    assert( b > h );
    assert( b > a );

    int i, n = ( b - a)/h;
    for(i = 1; i <= n-1; i++)
    {
      if(i%2==0)
      {
        s1=s1+function(a+i*h);
      }
      else
      {
        s2=s2+function(a+i*h);
      }
    }
    sum = h/3*(function(a)+function(b)+4*s2+2*s1);

    return sum;
}


Integral::Integral()
{
}


Integral::~Integral()
{
}
