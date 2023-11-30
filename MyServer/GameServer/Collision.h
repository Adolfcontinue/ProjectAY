#pragma once
#include "Float3.h"
#include "Math.h"

class Collision
{
public:
	static bool SphereToSphere(Float3& srcPos, double srcRadius, Float3& descPos, double descRadius);
};

