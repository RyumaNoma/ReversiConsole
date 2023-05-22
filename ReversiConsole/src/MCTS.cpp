#include "MCTS.hpp"
#include "Node.hpp"
#include "BitBoard.hpp"

MCTS::MCTS()
	: allocator_(100000)
	, SEARCH_TIME_(10)
	, sum_playout_(0)
	, turn_playout_(0)
{
}

MCTS::MCTS(int num_nodes, std::chrono::milliseconds::rep search_time)
	: allocator_(num_nodes)
	, SEARCH_TIME_(search_time)
	, sum_playout_(0)
	, turn_playout_(0)
{
}

void MCTS::Init()
{
	allocator_.Init();
	sum_playout_ = 0;
	turn_playout_ = 0;
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

int MCTS::AveragePlayout() const
{
	return sum_playout_ / turn_playout_;
}

std::chrono::milliseconds::rep MCTS::GetSearchTime() const
{
	return SEARCH_TIME_;
}
