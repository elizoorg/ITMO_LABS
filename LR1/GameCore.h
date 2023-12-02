#pragma once
#include <iostream>
#include <fstream>

#include "SavableRand.h"
#include "Utils.h"

class HammurabiGame
{
private:
	int wheat;
	int people;
	int acres;
	int turn;


	int wheatHarvestedPerAcre;
	int wheatHarvestedTotal;
	int wheatEaten;
	int peopleStarved;
	int peopleCame;
	bool plague;

	int totalPeople;
	int totalStarved;

	void printYearlyReport();
	bool askToSaveAndQuit();
public:
	const int START_WHEAT = 2800;
	const int START_PEOPLE = 100;
	const int START_ACRES = 1000;
	const int MAX_TURNS = 10;
	const int MAX_STUPID_INPUTS = 10;

	HammurabiGame();
	~HammurabiGame();
	void Play();
	void SaveTo(std::ofstream& stream);

	static HammurabiGame* LoadFrom(std::ifstream& stream);
};