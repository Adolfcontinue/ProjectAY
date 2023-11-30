#include "pch.h"
#include "Collision.h"
#include <cmath>

bool Collision::SphereToSphere(Float3& srcPos, double srcRadius, Float3& descPos, double descRadius)
{
	double dist = Math::Distance(srcPos, descPos);
	double subRadius = Math::Distance(srcRadius, descRadius);

	return dist <= subRadius;
}
