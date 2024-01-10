#pragma once
#include <math.h>
#include "Protocol.pb.h"


struct Float3
{
public:
	Float3(double x, double y, double z) : X(x), Y(y), Z(z) {}
	Float3() : X(0), Y(0), Z(0) {}
	Float3(Protocol::Float3 desc) : X(desc.x()), Y(desc.y()), Z(desc.z()) {}
	
	double X;
	double Y;
	double Z;

public:
	Protocol::Float3 Convert()
	{
		Protocol::Float3 retval;
		retval.set_x(X);
		retval.set_y(Y);
		retval.set_z(Z);

		return retval;
	}
};


struct Float4
{
public:
	Float4(double x, double y, double z, double w) : X(x), Y(y), Z(z), W(w) {}
	Float4() : X(0), Y(0), Z(0), W(0) {}
	Float4(Protocol::Float4 desc) : X(desc.x()), Y(desc.y()), Z(desc.z()), W(desc.w()) {}

	double X;
	double Y;
	double Z;
	double W;

public:
	Protocol::Float4 Convert()
	{
		Protocol::Float4 retval;
		retval.set_x(X);
		retval.set_y(Y);
		retval.set_z(Z);
		retval.set_w(W);

		return retval;
	}
};

