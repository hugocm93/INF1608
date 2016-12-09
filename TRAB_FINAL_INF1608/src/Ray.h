#ifndef RAY_H
#define RAY_H

class Vector3d;

class Ray
{

public:
	Ray( double originX, double originY, double originZ );

	~Ray();

double _x;
double _y;
double _z;

};
#endif
