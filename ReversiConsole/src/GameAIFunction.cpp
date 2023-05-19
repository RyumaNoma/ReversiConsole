#include "GameAIFunction.hpp"
#include "Point/Point.hpp"
#include "BitBoard.hpp"
#include "Random.hpp"

Point GameAIFunction::RandomAction(BitBoard* board, Random* random)
{
	auto legal = board->LegalPublic();
	int num_action = static_cast<int>(__popcnt64(legal));
	std::uint32_t index = random->Generate(num_action);
	// s“®‚Ì¶¬
	int count_action = 0;
	int count_bit = 0;
	while (legal)
	{
		if (legal & 1)
		{
			if (count_action == index)
			{
				return Point(count_bit % 8, count_bit / 8);
			}
			++count_action;
		}
		legal >>= 1;
		++count_bit;
	}
	return Point(-1, -1);
}

double GameAIFunction::Playout(BitBoard* board, Random* random)
{
	if (board->IsFinish())
	{
		return board->Result();
	}
	if (board->LegalPublic())
	{
		board->Act(RandomAction(board, random));
	}
	else
	{
		board->Swap();
	}
	return 1.0 - Playout(board, random);
}