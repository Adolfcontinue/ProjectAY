#pragma once
#include "Define.h"
#include "Protocol.pb.h"
#include "Struct.pb.h"
#include "Enum.pb.h"


class ProtobufHelper
{
public:
	static void ConvertFloat3(Protocol::Float3* outRet, float x, float y, float z)
	{
		outRet->set_x(x);
		outRet->set_y(y);
		outRet->set_z(z);
	}

	static void ConvertXMFLOAT3(DirectX::XMFLOAT3* outRet, const Protocol::Float3& srcData)
	{
		outRet->x = srcData.x();
		outRet->y = srcData.y();
		outRet->z = srcData.z();
	}

	static void ConvertFloat3(Protocol::Float3* outRet, DirectX::XMFLOAT3 srcData)
	{
		outRet->set_x(srcData.x);
		outRet->set_y(srcData.y);
		outRet->set_z(srcData.z);
	}

	static void ConvertFloat4(Protocol::Float4* ourRet, float x, float y, float z, float w)
	{
		ourRet->set_x(x);
		ourRet->set_y(y);
		ourRet->set_z(z);
		ourRet->set_w(w);
	}

	static void ConvertXMFLOAT4(DirectX::XMFLOAT4* outRet, const Protocol::Float4& srcData)
	{
		outRet->x = srcData.x();
		outRet->y = srcData.y();
		outRet->z = srcData.z();
		outRet->w = srcData.w();
	}

	static void ConvertFloat4(Protocol::Float4* ourRet, DirectX::XMFLOAT4 srcData)
	{
		ourRet->set_x(srcData.x);
		ourRet->set_y(srcData.y);
		ourRet->set_z(srcData.z);
		ourRet->set_w(srcData.w);
	}

};

