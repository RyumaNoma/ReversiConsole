#pragma once

class Point;
class BitBoard;

class Player
{
public:
	Player() {}
	virtual ~Player() {}

	/// <summary>
	/// 1試合の最初に呼び出す初期化処理
	/// </summary>
	virtual void Init() = 0;

	/// <summary>
	/// 1手分の行動を生成する
	/// </summary>
	/// <param name="board">行動を行う盤面</param>
	/// <returns>コマを置く場所</returns>
	virtual Point Act(const BitBoard& board) = 0;
};