#include "pch.h"
#include "Random.h"

std::random_device randomdevice;
std::mt19937 Random::geneator(randomdevice());


