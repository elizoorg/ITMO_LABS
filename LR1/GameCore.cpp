#include "GameCore.h"

HammurabiGame::HammurabiGame()
{
	SavableRand::Init();

	wheat = START_WHEAT;
	people = START_PEOPLE;
	acres = START_ACRES;
	turn = 1;

	wheatHarvestedTotal = 0;
	wheatHarvestedPerAcre = 0;
	wheatEaten = 0;
	peopleStarved = 0;
	peopleCame = 0;
	plague = false;


	totalPeople = 0;
	totalStarved = 0;
}

HammurabiGame::~HammurabiGame()
{
}

bool HammurabiGame::askToSaveAndQuit()
{
	while (true)
	{
		int result;
		std::cout << "Would you like to save and quit the game?\n1. Yes\n2. No\n> ";
		GetCorrectIntegerInput([](int x) { return x == 1 || x == 2; }, -1, "Please, enter 1 or 2.\n> ", &result);
		switch (result)
		{
		case 1:
		{
			std::ofstream file;
			file.open("save.hmr", std::ios::trunc);

			SaveTo(file);
			std::cout << "Done!" << std::endl;

			file.close();
			return true;
		}
		case 2:
			return false;
		}
	}
}

void HammurabiGame::printYearlyReport()
{
	std::cout << "Year: " << turn << " out of " << MAX_TURNS << std::endl;
	std::cout << "Your adviser comes to you:\n-Greetings, my king!\nHe pulls up a report" << std::endl;
	if (turn > 1)
	{
		std::cout << "-Since the last year:" << std::endl;
		if (peopleStarved > 0)
			std::cout << peopleStarved << " people starved to death" << std::endl;
		if (peopleCame > 0)
			std::cout << peopleCame << " new people came to the town" << std::endl;
		if (plague)
			std::cout << "There was a plague and half of the people died" << std::endl;
		else
			std::cout << "There was no plague" << std::endl;
		std::cout << wheatHarvestedTotal << " units of wheat were harvested, " << wheatHarvestedPerAcre << " units per acre" << std::endl;
		std::cout << wheatEaten << " units of wheat were eaten by rats" << std::endl;
	}
	std::cout << "-In your majesty's possession:" << std::endl;
	std::cout << people << " people" << std::endl;
	std::cout << wheat << " units of wheat in storages" << std::endl;
	std::cout << acres << " acres of land" << std::endl;
}

void HammurabiGame::Play()
{
	uint landPrice;
	int result;
	do
	{
		printYearlyReport();

		landPrice = SavableRand::Rand() % 10 + 17;
		std::cout << "-And currently land goes by " << landPrice << " units of wheat per acre" << std::endl;

		if (askToSaveAndQuit())
			return;

		std::cout << "-What will be your majesty's instructions:" << std::endl;
		std::cout << "-How much acres of land would you like to buy?\n> ";
		if (!GetCorrectIntegerInput([_wheat = wheat, landPrice](int x) { return x >= 0 && x <= _wheat / landPrice; }, 5, "-Sorry, i'm not sure i understand your instructions?\n>", &result))
		{
			std::cout << "Your subordinates thought you went crazy and dethroned you, game over." << std::endl;
			return;
		}
		if (result == 0)
		{
			std::cout << "-How much acres of land would you like to sell?\n> ";
			if (!GetCorrectIntegerInput([_wheat = wheat](int x) { return x >= 0 && x <= _wheat; }, MAX_STUPID_INPUTS, "-Sorry, i'm not sure we can do that?\n>", &result))
			{
				std::cout << "Your subordinates thought you went crazy and dethroned you, game over." << std::endl;
				return;
			}
			if (result > 0)
			{
				acres -= result;
				wheat += result * landPrice;
				std::cout << "-Done! " << result << " acres were sold and now " << acres << " acres of land and " << wheat << " units of wheat are in your majesty's possession" << std::endl;
			}
		}
		else
		{
			acres += result;
			wheat -= result * landPrice;
			std::cout << "-Done! " << result << " acres were bought and now " << acres << " acres of land and " << wheat << " units of wheat are in your majesty's possession" << std::endl;
		}

		std::cout << "-How much units of wheat would you like to be spent on food?\n> ";
		if (!GetCorrectIntegerInput([_wheat = wheat](int x) { return x >= 0 && x <= _wheat; }, MAX_STUPID_INPUTS, "-Sorry, i'm not sure we can do that?\n>", &result))
		{
			std::cout << "Your subordinates thought you went crazy and dethroned you, game over." << std::endl;
			return;
		}
		if (result > 0)
		{
			peopleStarved = std::max(0, people - (int)std::ceil(result / 20.0f));
			wheat -= result;
			std::cout << "-" << result << " units of wheat will be spent on food, " << wheat << " units of wheat are left in your majesty's possession" << std::endl;
		}

		std::cout << "-How much acres of land would you like us to sow with wheat?\n> ";
		if (!GetCorrectIntegerInput([_wheat = wheat, _acres = acres, _people = people](int x) { return x >= 0 && x <= _acres && x <= _wheat * 2 && x <= _people * 10; }, MAX_STUPID_INPUTS, "-Sorry, i'm not sure we can do that?\n>", &result))
		{
			std::cout << "Your subordinates thought you went crazy and dethroned you, game over." << std::endl;
			return;
		}
		if (result > 0)
		{
			wheat -= (int)std::ceil(result / 2.0f);
			wheatHarvestedPerAcre = SavableRand::Rand() % 6 + 1;
			wheatHarvestedTotal = wheatHarvestedPerAcre * result;
			std::cout << "-" << result << " acres will be sown with wheat, " << wheat << " units of wheat are left in your majesty's possession" << std::endl;
		}

		wheatEaten = (int)std::ceil(SavableRand::Rand() % ((int)((wheat + wheatHarvestedTotal) * 0.07f) + 1));
		peopleCame = (int)std::min(50.0f, std::max(0.0f, peopleStarved / 2.0f + (5.0f - wheatHarvestedTotal / (float)result) * (wheat + wheatHarvestedTotal - wheatEaten) / 600.0f + 1));
		plague = SavableRand::Rand() % 20 < 3;

		wheat = wheat + wheatHarvestedTotal - wheatEaten;
		people = people - peopleStarved + peopleCame;
		if (plague)
			people /= 2;

		totalPeople += people;
		totalStarved += peopleStarved;

		if (peopleStarved / (float)people > 0.45f)
		{
			if (people == 0)
				std::cout << "You have lost all your people, king without people is no king, game over." << std::endl;
			else
				std::cout << "Too many people starved to death, the ones who survived started a riot and dethroned you, game over." << std::endl;
			return;
		}

		std::cout << std::endl;
	} while (++turn <= MAX_TURNS);

	printYearlyReport();

	float starveAvg = totalStarved / (float)totalPeople;
	float acresPerPerson = acres / (float)people;

	if (starveAvg > 0.33f && acresPerPerson < 7.0f)
	{
		std::cout << "Due to your incompetence in town management, the people started a riot and dethroned you, game over." << std::endl;
		return;
	}
	if (starveAvg > 0.1f && acresPerPerson < 9.0f)
	{
		std::cout << "You ruled harshly. The people sighed in relief and went on, but no one wants to see you as the ruler again, game over." << std::endl;
		return;
	}
	if (starveAvg > 0.03f && acresPerPerson < 10.0f)
	{
		std::cout << "You did well, there were some people who didn't like you, but mostly your people would like to see you as a king again, well done." << std::endl;
		return;
	}
	std::cout << "You did great! Everyone is happy with their king and would like to see you as a king again, well done." << std::endl;
}

HammurabiGame* HammurabiGame::LoadFrom(std::ifstream& stream)
{
	HammurabiGame* game = new HammurabiGame();
	
	try
	{
		stream >> game->wheat;
		stream >> game->people;
		stream >> game->acres;
		stream >> game->turn;

		stream >> game->wheatHarvestedPerAcre;
		stream >> game->wheatHarvestedTotal;
		stream >> game->wheatEaten;
		stream >> game->peopleStarved;
		stream >> game->peopleCame;
		stream >> game->plague;

		uint seed = 0, sequenceLength = 1;
		stream >> seed;
		stream >> sequenceLength;
		SavableRand::Init(seed, sequenceLength - 1);

		stream >> game->totalPeople;
		stream >> game->totalStarved;

		return game;
	}
	catch (const std::exception& e)
	{
		return nullptr;
	}
}

void HammurabiGame::SaveTo(std::ofstream& stream)
{
	stream << wheat << std::endl;
	stream << people << std::endl;
	stream << acres << std::endl;
	stream << turn << std::endl;

	stream << wheatHarvestedPerAcre << std::endl;
	stream << wheatHarvestedTotal << std::endl;
	stream << wheatEaten << std::endl;
	stream << peopleStarved << std::endl;
	stream << peopleCame << std::endl;
	stream << plague << std::endl;

	stream << SavableRand::Seed << std::endl;
	stream << SavableRand::SequenceLength << std::endl;

	stream << totalPeople << std::endl;
	stream << totalStarved << std::endl;
}
