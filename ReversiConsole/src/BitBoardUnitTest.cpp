#include "BitBoardUnitTest.hpp"
#include "BitBoard.hpp"
#include "Point/Point.hpp"

void BitBoardUnitTest::Constructor()
{
	BitBoard b;
	BitBoard b2(b);
	std::cerr << "completed Constructor test" << std::endl;
}

void BitBoardUnitTest::Act()
{
	BitBoard b;
	bool success;
	success = b.Act(Point(3, 2));
	assert(success);
	b.Swap();
	success = b.Act(Point(4, 2));
	assert(success);
	std::cerr << b << std::endl;
	std::cerr << "completed Act Test" << std::endl;
}

void BitBoardUnitTest::ActError()
{
	BitBoard b;
	bool success;
	b.Swap();
	success = b.Act(Point(3, 2));
	assert(!success);
	success = b.Act(Point(7, 7));
	assert(!success);
	std::cerr << b << std::endl;
	std::cerr << "completed Act Error Test" << std::endl;
}

void BitBoardUnitTest::CountStones()
{
	bool success;
	BitBoard b;

	int me = b.CountStones(false);
	int opponent = b.CountStones(true);
	assert(2 == me);
	assert(2 == opponent);

	success = b.Act(Point(3, 2));
	assert(success);
	me = b.CountStones(false);
	opponent = b.CountStones(true);
	assert(4 == me);
	assert(1 == opponent);
	b.Swap();

	success = b.Act(Point(4, 2));
	assert(success);
	me = b.CountStones(false);
	opponent = b.CountStones(true);
	assert(3 == me);
	assert(3 == opponent);
	b.Swap();

	success = b.Act(Point(7, 7));
	assert(!success);
	me = b.CountStones(false);
	opponent = b.CountStones(true);
	assert(3 == me);
	assert(3 == opponent);
	b.Swap();

	std::cerr << b << std::endl;
	std::cerr << "completed CountStones Test" << std::endl;
}

void BitBoardUnitTest::LeftUpGame()
{
	BitBoard b;

	bool changed_board = true;
	while (changed_board)
	{
		changed_board = false;
		for (int y = 0; y < 8; ++y)
		{
			for (int x = 0; x < 8; ++x)
			{
				Point action(x, y);
				changed_board = b.Act(action);
				if (changed_board)
				{
					std::cerr << action << std::endl;
					break;
				}
			}
			if (changed_board)
			{
				break;
			}
		}
		b.Swap();
	}
	std::cerr << b << std::endl;
	std::cerr << "completed Left Up Game Test" << std::endl;
}

void BitBoardUnitTest::RightBottomGame()
{
	BitBoard b;

	bool changed_board = true;
	while (changed_board)
	{
		changed_board = false;
		for (int y = 7; y >= 0; --y)
		{
			for (int x = 7; x >= 0; --x)
			{
				Point action(x, y);
				changed_board = b.Act(action);
				if (changed_board)
				{
					std::cerr << action << std::endl;
					break;
				}
			}
			if (changed_board)
			{
				break;
			}
		}
		b.Swap();
	}
	std::cerr << b << std::endl;
	std::cerr << "completed Right Bottom Game Test" << std::endl;
}

void BitBoardUnitTest::NextPlayerSide()
{
	BitBoard b;
	BitBoard copy = b;
	copy.Swap();
	copy.Swap();
	assert(copy == b);

	std::cerr << "completed Next Player Side Test" << std::endl;
}

void BitBoardUnitTest::All()
{
	std::cerr << "start Test" << std::endl;
	Constructor();
	Act();
	ActError();
	CountStones();
	LeftUpGame();
	RightBottomGame();
	NextPlayerSide();
	std::cerr << "finish Test" << std::endl;
}