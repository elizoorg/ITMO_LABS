#include "SavableRand.h"

uint SavableRand::Seed;

uint SavableRand::SequenceLength;

void SavableRand::Init()
{
	Init((uint)std::time(NULL), 0);
}

void SavableRand::Init(uint seed, uint sequenceLength)
{
	Seed = seed;
	SequenceLength = sequenceLength;

	std::srand(seed);

#pragma warning(push)
#pragma warning(disable:6031)
	for (uint i = 0; i < sequenceLength; i++)
		std::rand();
#pragma warning(pop)
}

int SavableRand::Rand()
{
	SequenceLength++;
	return std::rand();
}