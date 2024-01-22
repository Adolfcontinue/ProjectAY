#pragma once
#include <math.h>
#include <cmath>
#include "Define.h"
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

	DirectX::XMFLOAT3 ConvertXMFlOAT3()
	{
		return DirectX::XMFLOAT3(X, Y, Z);
	}

	DirectX::XMVECTOR ConvertXMVECTOR()
	{
		DirectX::XMFLOAT3 temp = ConvertXMFlOAT3();
		return DirectX::XMLoadFloat3(&temp);
	}

	double Length()
	{
		DirectX::XMVECTOR ret = DirectX::XMVector3Length(ConvertXMVECTOR());
		return DirectX::XMVectorGetX(ret);
	}

	Float3 Normalize()
	{
		DirectX::XMVECTOR temp = DirectX::XMVector3Normalize(ConvertXMVECTOR());
		Float3 retVal;
		retVal.X = DirectX::XMVectorGetX(temp);
		retVal.Y = DirectX::XMVectorGetY(temp);
		retVal.Z = DirectX::XMVectorGetZ(temp);
		return retVal;
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
	void Set(double x, double y, double z, double w)
	{
		X = x;
		Y = y;
		Z = z;
		W = w;
	}


	Protocol::Float4 Convert()
	{
		Protocol::Float4 retval;
		retval.set_x(X);
		retval.set_y(Y);
		retval.set_z(Z);
		retval.set_w(W);

		return retval;
	}

	DirectX::XMFLOAT4 ConvertXMFlOAT4()
	{
		return DirectX::XMFLOAT4(X, Y, Z, W);
	}

	DirectX::XMVECTOR ConvertXMVECTOR()
	{
		DirectX::XMFLOAT4 temp = ConvertXMFlOAT4();
		return DirectX::XMLoadFloat4(&temp);
	}

	double Length()
	{
		DirectX::XMVECTOR ret = DirectX::XMVector4Length(ConvertXMVECTOR());
		return DirectX::XMVectorGetX(ret);
	}

	Float3 Normalize()
	{
		DirectX::XMVECTOR temp = DirectX::XMVector4Normalize(ConvertXMVECTOR());
		Float3 retVal;
		retVal.X = DirectX::XMVectorGetX(temp);
		retVal.Y = DirectX::XMVectorGetY(temp);
		retVal.Z = DirectX::XMVectorGetZ(temp);
		return retVal;
	}

	void RotateAxisZ(float radian)
	{
		DirectX::XMVECTOR rotationQuaternion = DirectX::XMQuaternionRotationAxis(AXIS_Z, radian);
		DirectX::XMVECTOR rotation = DirectX::XMQuaternionMultiply(ConvertXMVECTOR(), rotationQuaternion);
		
		Set(DirectX::XMVectorGetX(rotation), DirectX::XMVectorGetY(rotation), DirectX::XMVectorGetZ(rotation), DirectX::XMVectorGetW(rotation));
	}
};

