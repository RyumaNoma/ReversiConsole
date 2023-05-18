#include "NodeUnitTest.hpp"
#include "Node.hpp"
#include "BitBoard.hpp"
#include <cassert>

void NodeUnitTest::ExpandTest()
{
	Node node;
	Allocator<Node> allcator(100);
	BitBoard board;

	node.Expand(board, allcator);
	for (auto child : node.children_)
	{
		std::cout << *child << std::endl << std::endl;
	}
}

void NodeUnitTest::AllTest()
{
	std::cout << "Start Test" << std::endl;
	ExpandTest();
	std::cout << "Finish Test" << std::endl;
}