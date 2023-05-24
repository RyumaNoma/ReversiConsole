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

	const int Mergin = static_cast<int>(height * 0.1);
	const int BoardSize = static_cast<int>(height * 0.1);
	const int CellSize = BoardSize / 8;

	std::uint64_t legal = board.LegalPublic();
	while (true)
	{
		int mouse_input = GetMouseInput();
		if (mouse_input & MOUSE_INPUT_LEFT)
		{
			int mouse_x, mouse_y;
			GetMousePoint(&mouse_x, &mouse_y);
			
			if (mouse_x < Mergin || Mergin + BoardSize < mouse_x) continue;
			if (mouse_y < Mergin || Mergin + BoardSize < mouse_y) continue;

			int x = (mouse_x - Mergin) / CellSize;
			int y = (mouse_y - Mergin) / CellSize;
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
