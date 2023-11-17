#pragma once

struct SVector
{
public:
	SVector(double x, double y, double z) : _x(x), _y(y), _z(z) {}
	SVector() : _x(0), _y(0), _z(0) {}

	double _x;
	double _y;
	double _z;
};

