#include "MCTS.hpp"
#include "Node.hpp"
#include "BitBoard.hpp"

MCTS::MCTS()
	: allocator_(100000)
	, SEARCH_TIME_(10)
{
}

MCTS::MCTS(int num_nodes, std::chrono::milliseconds::rep search_time)
	: allocator_(num_nodes)
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
	root.Expand(board, allocator_);

	Timer timer;
	int count = 0;
	while (timer.ElapsedMilliseconds() < SEARCH_TIME_)
	{
		BitBoard copy = board;
		root.Evaluate(copy, allocator_, random_);
		++count;
	}
	// std::cout << "count:" << count << std::endl;
	return root.SelectBestAction();
}