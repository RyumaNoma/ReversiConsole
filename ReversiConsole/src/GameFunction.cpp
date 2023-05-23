#include "GameFunction.hpp"
#include "DxLib.h"

std::pair<int, int> GameFunction::GetWindowSize()
{
	int width, height;
	::GetWindowSize(&width, &height);
	return std::make_pair(width, height);
}
