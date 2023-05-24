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

	/// <summary>
	/// ゲームをフルスクリーンモードに変更する
	/// </summary>
	static void ChangeToFullScreenMode();

	/// <summary>
	/// ゲームをウィンドウモードに変更する
	/// </summary>
	/// <param name="width">ウィンドウの横幅</param>
	/// <param name="height">ウィンドウの縦幅</param>
	static void ChangeToWindowMode(int width, int height);
};