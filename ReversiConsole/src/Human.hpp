#pragma once
#include "Player.hpp"

class Human
	: public Player
{
public:
	void Init();
	Point Act(const BitBoard& board);
};