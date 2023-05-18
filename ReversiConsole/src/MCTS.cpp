#include "MCTS.hpp"
#include "Node.hpp"
#include "BitBoard.hpp"

MCTS::MCTS()
	: allocator_(100000)
	, C_(1.0)
	, EXPAND_THRESHOLD_(2)
	, SEARCH_TIME_(10)
{
}

MCTS::MCTS(int num_nodes, double C, int expand_thresold, std::chrono::milliseconds::rep search_time)
	: allocator_(num_nodes)
	, C_(C)
	, EXPAND_THRESHOLD_(expand_thresold)
	, SEARCH_TIME_(search_time)
{
}

void MCTS::Init()
{
	allocator_.Init();
}

Point MCTS::Act(const BitBoard& board)
{
	Node root;
	root.Expand(board);

	Timer timer;
	while (timer.ElapsedMilliseconds() < SEARCH_TIME_)
	{
		BitBoard copy = board;
		root.Evaluate(&copy);
	}
	return root.SelectBestAction();
}