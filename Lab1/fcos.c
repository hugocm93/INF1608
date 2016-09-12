#include "fcos.h"

const double halfPi = PI/2;
const double oneDividedBy3Fac = 1./6;
const double halfPiToTheSecond = halfPi*halfPi;
const double piToTheSecondDividedBy2 = PI*halfPi;
const double halfPiToTheThird = halfPi*halfPi*halfPi;

double fcos ( double x )
{
  return halfPi + oneDividedBy3Fac*( x*x*x -x*x*PI + halfPiToTheSecond*x -halfPi*x*x + x*piToTheSecondDividedBy2 - halfPiToTheThird ) - x;
}
