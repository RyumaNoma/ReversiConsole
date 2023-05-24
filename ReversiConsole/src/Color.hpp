#pragma once
#include "DxLib.h"
class Color
{
public:
	// �^�C�g��
	static constexpr unsigned int GAME_TITLE = 0xFFFFFF;
	static constexpr unsigned int TITLE_EXPLAIN_KEY_CHAR = 0xFFFFFF;
	static constexpr unsigned int TITLE_BACKGROUND = 0xF4ADA3;
	// �����O
	static constexpr unsigned int BEFORE_MATCH_EFFECT_BAND = 0xFF0000;
	static constexpr unsigned int BEFORE_MATCH_EFFECT_CHAR = 0xFFFFFF;
	// ������
	static constexpr unsigned int LEGAL_ACTION_EFFECT = 0xC0C0C0;
	static constexpr unsigned int PASS_EFFECT_BAND = 0xF4ADA3;
	static constexpr unsigned int PASS_EFFECT_CHAR = 0x000000;
	static constexpr unsigned int SWAP_EFFECT = 0xF4ADA3;
	// �Ֆ�
	static constexpr unsigned int BOARD_BACKGROUND = 0x00FF00;
	static constexpr unsigned int BOARD_LINE = 0x000000;
	static constexpr unsigned int FIRST_PLAYER_STONE = 0x000000;
	static constexpr unsigned int SECOND_PLAYER_STONE = 0xFFFFFF;
	// ����
	static constexpr unsigned int RESULT_TITLE_CHAR = 0xFFFFFF;
	static constexpr unsigned int RESULT_WIN_CHAR = 0xFF0000;
	static constexpr unsigned int RESULT_DRAW_CHAR = 0xFFFFFF;
	static constexpr unsigned int RESULT_LOSE_CHAR = 0x0000FF;
	static constexpr unsigned int RESULT_STONES_CHAR = 0xFFFFFF;
	static constexpr unsigned int RESULT_EXPLAIN_KEY_CHAR = 0xFFFFFF;
};