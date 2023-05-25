#pragma once
#include <utility>
#include <string>

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

	/// <summary>
	/// 文字列を中央ぞろえにするための左上の座標を求める．
	/// </summary>
	/// <param name="x1">左端の座標</param>
	/// <param name="y1">上端の座標</param>
	/// <param name="x2">右端の座標</param>
	/// <param name="y2">下端の座標</param>
	/// <param name="text">表示する文字列</param>
	/// <param name="font_size">表示する際のフォントサイズ</param>
	/// <returns>左上の座標</returns>
	static std::pair<int, int> GetLeftTopToAlignCenter(int x1, int y1, int x2, int y2, std::string text, int font_size);
};