#include "Human.hpp"
#include <iostream>
#include "Point/Point.hpp"
#include "BitBoard.hpp"
#include "DxLib.h"
#include "GameFunction.hpp"

void Human::Init()
{
}

Point Human::Act(const BitBoard& board)
{
	// demo
	return LeftUp(board);

	// ‰æ–ÊƒTƒCƒY‚ÌŽæ“¾

	auto [width, height] = GameFunction::GetWindowSize();

	const int mergin = height * 0.1;
	const int board_size = height * 0.8;
	const int cell_size = board_size / 8;

	std::uint64_t legal = board.LegalPublic();
	while (true)
	{
		int mouse_input = GetMouseInput();
		if (mouse_input & MOUSE_INPUT_LEFT)
		{
			int mouse_x, mouse_y;
			GetMousePoint(&mouse_x, &mouse_y);
			
			if (mouse_x < mergin || mergin + board_size < mouse_x) continue;
			if (mouse_y < mergin || mergin + board_size < mouse_y) continue;

			int x = (mouse_x - mergin) / cell_size;
			int y = (mouse_y - mergin) / cell_size;
			int hash = y * 8 + x;
			if ((legal & (1ULL << hash)) == 0) continue;
			return Point(x, y);
		}
	}
}

Point Human::LeftUp(const BitBoard& board) const
{
	return board.LegalActions()[0];
}
