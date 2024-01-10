#pragma once
#include <cmath>
#include "Float3.h"

class Math
{
public:
	static double Distance(Float3& src, Float3& desc)
	{
		double distX = pow(abs(src.X - desc.X), 2);
		double distY = pow(abs(src.Y - desc.Y), 2);
		double distZ = pow(abs(src.Z - desc.Z), 2);

		return sqrt(distX + distY + distX);
	}

	static double Distance(double src, double desc)
	{
		return abs(src - desc);
	}
		
};
