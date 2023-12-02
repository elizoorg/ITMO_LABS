#pragma once
#include <ctime>
#include <random>

#define uint unsigned int


class SavableRand final
{
public:
	static uint Seed;
	static uint SequenceLength;
	static void Init();
	static void Init(uint seed, uint sequenceLength);
	static int Rand();
private:
	SavableRand() {};
};