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

std::pair<int, int> GameFunction::GetLeftTopToAlignCenter(int x1, int y1, int x2, int y2, std::string text, int font_size)
{
	int width = x2 - x1;
	int height = y2 - y1;
	int text_length = static_cast<int>(text.size());
	std::pair<int, int> left_top;

	left_top.first = (width - GetDrawStringWidth(text.c_str(), text_length)) / 2 + x1;
	left_top.second = (height - font_size) / 2 + y1;

	return left_top;
}
