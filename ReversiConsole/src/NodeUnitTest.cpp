#include "NodeUnitTest.hpp"
#include "Node.hpp"
#include "BitBoard.hpp"
#include "Random.hpp"
#include <cassert>

void NodeUnitTest::ExpandTest()
{
	std::cout << "Start Expand Test" << std::endl;
	Node node;
	Allocator<Node> allcator(100);
	BitBoard board;
	const Point expected_actions[4] = {
		Point(3, 2),
		Point(2, 3),
		Point(5, 4),
		Point(4, 5)
	};

	node.Expand(board, allcator);
	for (int i = 0; i < node.children_.size(); ++i)
	{
		auto child = node.children_[i];
		assert(child->action_ == expected_actions[i]);
		assert(child->children_.size() == 0);
		assert(child->n_ == 0);
		assert(child->w_ == 0);
		assert(child->ww_ == 0);
	}
	std::cout << "Finish Expand Test" << std::endl;
}

void NodeUnitTest::EvaluateTest()
{
	std::cout << "Start Evaluate Test" << std::endl;
	Node node;
	Allocator<Node> allocator(100000);
	Random random;
	BitBoard b;
	node.Expand(b, allocator);

	for (int i = 0; i < 1000; ++i)
	{
		BitBoard board;
		double result = node.Evaluate(board, allocator, random);
	}
	std::cout << node << std::endl << std::endl;
	for (auto child : node.children_)
	{
		std::cout << *child << std::endl << std::endl;
	}
	std::cout << "Allocated Node: " << allocator.CountBlocks() << std::endl;
	std::cout << "Finish Evaluate Test" << std::endl;
}

void NodeUnitTest::AllTest()
{
	std::cout << "Start Test" << std::endl;
	ExpandTest();
	EvaluateTest();
	std::cout << "Finish Test" << std::endl;
}