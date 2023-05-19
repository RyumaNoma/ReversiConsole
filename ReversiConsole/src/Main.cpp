#include <iostream>
#include "BitBoard.hpp"
#include "Human.hpp"
#include "MCTS.hpp"
#include <cassert>
#define GAMES 100

int main(void)
{
	double result = 0;
	Human human;
	MCTS mcts1(100000, 1);
	MCTS mcts2(100000, 10);
	Human h;

	for (int i = 0; i < GAMES; ++i)
	{
		BitBoard board;
		board.Init();
		mcts1.Init();
		mcts2.Init();
		int turn = 0;
		while (!board.IsFinish())
		{
			// PASS‚µ‚©‚Å‚«‚È‚¢ê‡
			if (board.LegalPublic() == 0)
			{
				board.Swap();
				continue;
			}
			if (board.LegalPublic() != 0)
			{
				Point action;
				if (turn % 2)
				{
					do
					{
						action = mcts1.Act(board);
					} while (!board.Act(action));
				}
				else
				{
					do
					{
						action = mcts2.Act(board);
						//action = h.Act(board);
					} while (!board.Act(action));
				}
			}
			++turn;
		}
		if (turn % 2)
		{
			result += 1 - board.Result();
		}
		else
		{
			result += board.Result();
		}
		std::cout << "Game" << i << std::endl;
		std::cout << board << std::endl;
	}
	std::cout << "result: " << result << std::endl;
}