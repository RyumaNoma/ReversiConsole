#pragma once
#include "DxLib.h"
class Color
{
private:
	static constexpr unsigned int WHITE = 0xFFFFFF;
	static constexpr unsigned int BLACK = 0x000000;
	static constexpr unsigned int RED = 0xFF00FF;
	static constexpr unsigned int GREEN = 0x00FF00;
	static constexpr unsigned int BLUE = 0x0000FF;
public:
	// 全体
	static constexpr unsigned int BACKGROUND = 0xBFBFBF;
	static constexpr unsigned int BACKGROUND_R = (BACKGROUND >> 8 * 2) & 0xFF;
	static constexpr unsigned int BACKGROUND_G = (BACKGROUND >> 8 * 1) & 0xFF;
	static constexpr unsigned int BACKGROUND_B = (BACKGROUND >> 8 * 0) & 0xFF;
	// タイトル
	static constexpr unsigned int GAME_TITLE = WHITE;
	// 試合前
	static constexpr unsigned int BEFORE_MATCH_EFFECT_BAND = 0x636363;
	static constexpr unsigned int BEFORE_MATCH_EFFECT_CHAR = WHITE;
	// 試合中
	static constexpr unsigned int LEGAL_ACTION_EFFECT = 0xC0C0C0;
	static constexpr unsigned int PASS_EFFECT_BAND = 0xF4ADA3;
	static constexpr unsigned int PASS_EFFECT_CHAR = BLACK;
	static constexpr unsigned int SWAP_EFFECT = 0xF4ADA3;
	// 盤面
	static constexpr unsigned int BOARD_BACKGROUND = WHITE;
	static constexpr unsigned int BOARD_LINE = BLACK;
	static constexpr unsigned int FIRST_PLAYER_STONE = 0x18FAFF;
	static constexpr unsigned int SECOND_PLAYER_STONE = 0xFF1F91;
	// 結果
	static constexpr unsigned int RESULT_TITLE_CHAR = WHITE;
	static constexpr unsigned int RESULT_WIN_CHAR = RED;
	static constexpr unsigned int RESULT_DRAW_CHAR = WHITE;
	static constexpr unsigned int RESULT_LOSE_CHAR = BLUE;
	static constexpr unsigned int RESULT_STONES_CHAR = WHITE;
	// ボタン
	static constexpr unsigned int BUTTON_BACKGROUND = 0x636363;
	static constexpr unsigned int BUTTON_CHAR = WHITE;
};