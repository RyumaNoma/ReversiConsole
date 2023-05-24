#pragma once
#include "Player.hpp"

class Human
	: public Player
{
public:
	void Init();
	Point Act(const BitBoard& board);

	/// <summary>
	/// 合法手の内，最も左上のものを求める．
	/// デバッグ用．
	/// </summary>
	/// <param name="board">盤面</param>
	/// <returns>最も左上の合法手</returns>
	Point LeftUp(const BitBoard& board) const;
};