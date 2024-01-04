#pragma once
#include "Protocol.pb.h"
#include "Struct.pb.h"
#include "Enum.pb.h"


class ProtobufHelper
{
public:
	static void ConvertVector(Protocol::Vector* outRet, double x, double y, double z)
	{
		outRet->set_x(x);
		outRet->set_y(y);
		outRet->set_z(z);
	}
};

