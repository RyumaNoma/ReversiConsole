#pragma once
#include <utility>

class GameFunction
{
public:
	/// <summary>
	/// ゲーム画面のサイズを取得する
	/// </summary>
	/// <returns>(横の長さ，縦の長さ)</returns>
	static std::pair<int, int> GetWindowSize();
};