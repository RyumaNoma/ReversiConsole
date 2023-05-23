#pragma once
#include "Player.hpp"

class Human
	: public Player
{
public:
	void Init();
	Point Act(const BitBoard& board);
	Point LeftUp(const BitBoard& board) const;
};