#include "BitBoard.hpp"
#include <intrin.h>
#include <cassert>
#include "Point/Point.hpp"

#define EMPTY_MASK 0x0
#define FULL_MASK 0xFFFFFFFFFFFFFFFF

BitBoard::BitBoard()
{
	Init();
}

BitBoard::BitBoard(const BitBoard& bit_board)
{
	for (int i = 0; i < 2; ++i)
	{
		board_[i] = bit_board.board_[i];
	}
}

void BitBoard::Init()
{
	// 左下と右上
	board_[0] = 0x0000000810000000;
	// 左上と右下
	board_[1] = 0x0000001008000000;
}

bool BitBoard::Act(Point action)
{
	auto legal = Legal(board_[0], board_[1]);

	// 盤面外のマスの指定
	int stone_index = action.y() * 8 + action.x();
	if (stone_index < 0 || 63 < stone_index)
	{
		return false;
	}
	Board position = 1ULL << stone_index;

	if (position & legal)
	{
		Reverse(action);
		return true;
	}
	return false;
}

int BitBoard::CountStones(bool is_opponent) const
{
	return __popcnt64( board_[ static_cast<std::uint8_t>(is_opponent) ] );
}

bool BitBoard::IsFinish() const
{
	bool both_pass = (Legal(board_[0], board_[1]) == EMPTY_MASK && Legal(board_[1], board_[0]) == EMPTY_MASK);
	bool filled = ((board_[0] | board_[1]) == FULL_MASK);

	return both_pass || filled;
}

bool BitBoard::IsExistLegal() const
{
	auto legal = Legal(board_[0], board_[1]);
	return legal != EMPTY_MASK;
}

BitBoard::Board BitBoard::LegalPublic() const
{
	return Legal(board_[0], board_[1]);
}

void BitBoard::Swap()
{
	std::swap(board_[0], board_[1]);
}

bool BitBoard::IsLose() const
{
	int me = CountStones(false);
	int opponent = CountStones(true);

	return (IsFinish() && opponent > me);
}

bool BitBoard::IsDraw() const
{
	int me = CountStones(false);
	int opponent = CountStones(true);

	return (IsFinish() && opponent == me);
}

bool BitBoard::operator==(const BitBoard& bitboard) const {
	return (board_[0] == bitboard.board_[0] && board_[1] == bitboard.board_[1]);
}

bool BitBoard::operator!=(const BitBoard& bitboard) const {
	return (!(*this == bitboard));
}

std::ostream& operator<<(std::ostream& os, const BitBoard& bit_board)
{
	std::uint64_t mask = 0x1;
	os << "  0 1 2 3 4 5 6 7\n";
	for (int y = 0; y < 8; ++y)
	{
		os << y << ' ';
		for (int x = 0; x < 8; ++x)
		{
			if (bit_board.board_[0] & mask)
			{
				os << 'x';
			}
			else if (bit_board.board_[1] & mask)
			{
				os << 'o';
			}
			else
			{
				os << '_';
			}
			os << ' ';

			mask <<= 1;
		}
		os << '\n';
	}
	return os;
}