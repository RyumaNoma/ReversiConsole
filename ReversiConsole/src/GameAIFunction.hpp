#pragma once

class BitBoard;
class Point;
class Random;

class GameAIFunction
{
public:
	/// <summary>
	/// 合法手からランダムに一つ選ぶ
	/// </summary>
	/// <param name="board">盤面</param>
	/// <returns>ランダムに選ばれた合法手</returns>
	static Point RandomAction(BitBoard* board, Random* random);
	/// <summary>
	/// ランダムプレイアウトを1試合行う
	/// </summary>
	/// <param name="board">開始状態</param>
	/// <returns>結果(win:1, draw:0.5, lose:0)</returns>
	static double Playout(BitBoard* board, Random* random);
};

