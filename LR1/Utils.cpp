#include "Utils.h"

bool GetCorrectIntegerInput(std::function<bool(int x)> validator, int tries, const char* errorMessage, int* result)
{

	while (!(std::cin >> *result) || !validator(*result))
	{
		if (std::cin.fail())
		{
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
		if (tries > 0 && --tries == 0)
			return false;
		std::cout << errorMessage;
	}

	return true;
}