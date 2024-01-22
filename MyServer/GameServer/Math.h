#pragma once
#include "Define.h"
#include <cmath>
#include "Float3.h"

using namespace DirectX;

class Math
{
public:
	static double Distance(Float3& src, Float3& desc)
	{
		double distX = pow(src.X - desc.X, 2);
		double distY = pow(src.Y - desc.Y, 2);
		double distZ = pow(src.Z - desc.Z, 2);

		return sqrt(distX + distY + distX);
	}

	static double Distance(double src, double desc)
	{
		return abs(src - desc);
	}
	
	static double AngleBetweenTwoVectors(Float3 src, Float3 desc)
	{
		XMVECTOR temp = XMVector4AngleBetweenVectors(src.ConvertXMVECTOR(), desc.ConvertXMVECTOR());
		return XMConvertToDegrees(XMVectorGetX(XMVector4AngleBetweenVectors(src.ConvertXMVECTOR(), desc.ConvertXMVECTOR())));
	}

	static float DegreeToRadian(float degree)
	{
		return DirectX::XMConvertToRadians(degree);
	}

	static float RadianToDegree(float radian)
	{
		return DirectX::XMConvertToDegrees(radian);
	}
};
