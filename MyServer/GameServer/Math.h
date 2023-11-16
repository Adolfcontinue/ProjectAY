#pragma once
#include <cmath>
#include "SVector.h"

class Math
{
public:
	static double Distance(SVector& src, SVector& desc)
	{
		double distX = pow(abs(src._x - desc._x), 2);
		double distY = pow(abs(src._y - desc._y), 2);
		double distZ = pow(abs(src._z - desc._z), 2);

		return sqrt(distX + distY + distX);
	}

	static double Distance(double src, double desc)
	{
		return abs(src - desc);
	}
		
};

