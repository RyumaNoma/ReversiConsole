#pragma once
#include "Player.hpp"

class Human
	: public Player
{
public:
	void Init();
	Point Act(const BitBoard& board);

	/// <summary>
	/// ���@��̓��C�ł�����̂��̂����߂�D
	/// �f�o�b�O�p�D
	/// </summary>
	/// <param name="board">�Ֆ�</param>
	/// <returns>�ł�����̍��@��</returns>
	Point LeftUp(const BitBoard& board) const;
};