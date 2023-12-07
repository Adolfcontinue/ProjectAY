#pragma once
#include <math.h>
#include "Protocol.pb.h"


struct Float3
{
public:
	Float3(double x, double y, double z) : _x(x), _y(y), _z(z) {}
	Float3() : _x(0), _y(0), _z(0) {}

	double _x;
	double _y;
	double _z;

public:
	Protocol::Vector Convert()
	{
		Protocol::Vector retval;
		retval.set_x(_x);
		retval.set_y(_y);
		retval.set_z(_z);

		return retval;
	}
};

