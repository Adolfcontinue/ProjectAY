#include "pch.h"
#include "Collision.h"
#include <cmath>

bool Collision::SphereToSphere(SVector& srcPos, double srcRadius, SVector& descPos, double descRadius)
{
	double dist = Math::Distance(srcPos, descPos);

	double subRadius = Math::Distance(srcRadius, descRadius);

	return dist <= subRadius;
}
