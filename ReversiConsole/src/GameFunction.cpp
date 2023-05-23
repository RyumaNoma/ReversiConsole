#include "GameFunction.hpp"

std::pair<int, int> GameFunction::GetScreenSize()
{
	int width, height, bit;
	GetScreenState(&width, &height, &bit);
	return std::make_pair(width, height);
}
