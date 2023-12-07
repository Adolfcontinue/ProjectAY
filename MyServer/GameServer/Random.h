#pragma once
#include "random"

class Random
{
	static std::mt19937 gen;
public:
	static uint64 Get(uint64 begin, uint64 end);
};

