#include "Human.hpp"
#include <iostream>
#include "Point/Point.hpp"

void Human::Init()
{
}

Point Human::Act(const BitBoard& board)
{
	int x, y;
	std::cout << "X: ";
	std::cin >> x;
	std::cout << "Y: ";
	std::cin >> y;

	return Point(x, y);
}