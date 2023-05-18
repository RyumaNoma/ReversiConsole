#pragma once

class BitBoard;
class Point;
class Random;

class GameAIFunction
{
public:
	/// <summary>
	/// ���@�肩�烉���_���Ɉ�I��
	/// </summary>
	/// <param name="board">�Ֆ�</param>
	/// <returns>�����_���ɑI�΂ꂽ���@��</returns>
	static Point RandomAction(BitBoard* board, Random* random);
	/// <summary>
	/// �����_���v���C�A�E�g��1�����s��
	/// </summary>
	/// <param name="board">�J�n���</param>
	/// <returns>����(win:1, draw:0.5, lose:0)</returns>
	static double Playout(BitBoard* board, Random* random);
};

