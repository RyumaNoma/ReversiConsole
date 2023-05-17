#include "BitBoard.hpp"
#include <iostream>
#include <cassert>
#include "Point/Point.hpp"

const BitBoard::Board BitBoard::kHorizontalEdge = 0x7e7e7e7e7e7e7e7e;
const BitBoard::Board BitBoard::kVerticalEdge = 0x00ffffffffffff00;
const BitBoard::Board BitBoard::kDiagonalEdge = 0x007e7e7e7e7e7e00;

BitBoard::Board BitBoard::shl(Board a, std::uint32_t b)
{
	return a << b;
}

BitBoard::Board BitBoard::shr(Board a, std::uint32_t b)
{
	return a >> b;
}

BitBoard::Board BitBoard::Line(Board me, Board mask, ShiftFunc shift, int n)
{
	Board result = 0;
	result |= mask & shift(me, n);
	for (int i = 0; i < 5; ++i)
	{
		result |= mask & shift(result, n);
	}
	return result;
}

BitBoard::Board BitBoard::Legal(Board me, Board opponent)
{
	auto calc = [&](Board mask, int n) -> Board
	{
		mask &= opponent;
		Board buffer, result = 0;

		buffer = Line(me, mask, shl, n);
		result |= shl(buffer, n);
		buffer = Line(me, mask, shr, n);
		result |= shr(buffer, n);
		return result;
	};

	Board result = 0;
	result |= calc(kHorizontalEdge, 1);
	result |= calc(kDiagonalEdge, 7);
	result |= calc(kVerticalEdge, 8);
	result |= calc(kDiagonalEdge, 9);
	return result & (~(me | opponent));
}

BitBoard::Board BitBoard::ReverseStones(Board me, Board opponent, Board position)
{
	auto calc = [&](Board mask, int n) -> Board
	{
		mask &= opponent;
		Board buffer;
		Board result = 0;

		buffer = Line(position, mask, shl, n);
		if ((me & shl(buffer, n)) != 0) { result |= buffer; }
		buffer = Line(position, mask, shr, n);
		if ((me & shr(buffer, n)) != 0) { result |= buffer; }
		return result;
	};

	Board result = 0;
	result |= calc(kHorizontalEdge, 1);
	result |= calc(kDiagonalEdge, 7);
	result |= calc(kVerticalEdge, 8);
	result |= calc(kDiagonalEdge, 9);
	return result;
}

void BitBoard::Reverse(Point action)
{
	// 盤面外のマスの指定
	int stone_index = action.y() * 8 + action.x();
	if (stone_index < 0 || stone_index > 63)
	{
		return;
	}
	Board position = 1ULL << stone_index;

	Board reverse_stones = ReverseStones(board_[0], board_[1], position);
	// 反転処理
	board_[0] ^= position ^ reverse_stones;
	board_[1] ^= reverse_stones;
}