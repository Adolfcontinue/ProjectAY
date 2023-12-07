#pragma once
#include <cmath>
#include "Float3.h"

class Math
{
public:
	static double Distance(Float3& src, Float3& desc)
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
