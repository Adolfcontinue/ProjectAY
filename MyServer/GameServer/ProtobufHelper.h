#pragma once
#include "Protocol.pb.h"
#include "Struct.pb.h"
#include "Enum.pb.h"
#include "Float3.h"


class ProtobufConverter
{
public:
	static void ConvertFloat3(Protocol::Float3* outRet, double x, double y, double z)
	{
		outRet->set_x(x);
		outRet->set_y(y);
		outRet->set_z(z);
	}

	static void ConvertFloat3(Protocol::Float3* outRet, Float3 src)
	{

	}

	static void ConvertFloat4(Protocol::Float4* ourRet, double x, double y, double z, double w)
	{
		ourRet->set_x(x);
		ourRet->set_y(y);
		ourRet->set_z(z);
		ourRet->set_w(w);
	}

	static void ConvertFloat4(Protocol::Float4* outRet, Float4 src)
	{

	}

};

