#include "pch.h"
#include "Random.h"

std::random_device rd;
std::mt19937 Random::gen(rd());

uint64 Random::Get(uint64 begin, uint64 end)
{
    std::uniform_int_distribution<uint64> dis(begin, end);
    return dis(gen);
}

