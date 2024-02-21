#pragma once
#include "random"

class Random
{
	static std::mt19937 geneator;
public:
	template<typename T>
	static T GetRandom(T min, T max)
	{
		std::uniform_int_distribution<T> distribute(min, max);
		return distribute(geneator);
	}
};

