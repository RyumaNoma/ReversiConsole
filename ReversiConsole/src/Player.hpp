#pragma once

class Point;
class BitBoard;

class Player
{
public:
	Player() {}
	virtual ~Player() {}

	/// <summary>
	/// 1�����̍ŏ��ɌĂяo������������
	/// </summary>
	virtual void Init() = 0;

	/// <summary>
	/// 1�蕪�̍s���𐶐�����
	/// </summary>
	/// <param name="board">�s�����s���Ֆ�</param>
	/// <returns>�R�}��u���ꏊ</returns>
	virtual Point Act(const BitBoard& board) = 0;
};