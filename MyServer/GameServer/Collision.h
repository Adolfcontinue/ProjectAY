#pragma once
#include "SVector.h"
#include "Math.h"

class Collision
{
public:
	static bool SphereToSphere(SVector& srcPos, double srcRadius, SVector& descPos, double descRadius);
};

