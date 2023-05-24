#include "GameFunction.hpp"
#include "DxLib.h"

std::pair<int, int> GameFunction::GetWindowSize()
{
	int width, height;
	::GetWindowSize(&width, &height);
	return std::make_pair(width, height);
}

void GameFunction::ChangeToFullScreenMode()
{
	int desktop_w, desktop_h;
	GetDefaultState(&desktop_w, &desktop_h, NULL);
	SetGraphMode(desktop_w, desktop_h, 32);
	ChangeWindowMode(false);
}

void GameFunction::ChangeToWindowMode(int width, int height)
{
	SetGraphMode(width, height, 32);
	SetWindowSize(width, height);
	ChangeWindowMode(true);
}
