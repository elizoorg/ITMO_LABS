#pragma once
#include <iostream>
#include <fstream>
#include <functional>


bool GetCorrectIntegerInput(std::function<bool(int x)> validator, int tries, const char* errorMessage, int* result);