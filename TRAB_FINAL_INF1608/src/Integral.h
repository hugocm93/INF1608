#ifndef INTEGRAL_H
#define INTEGRAL_H

#include <functional>

class Integral
{
public:

static double simpson( std::function< double ( double ) >& function , double a, double b, double h );

private:

Integral();

~Integral();

};
#endif
