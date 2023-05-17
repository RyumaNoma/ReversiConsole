#pragma once
#include "Point/Point.hpp"
#include <vector>

class BitBoard;

class Node
{
public:
	Node();
	/// <summary>
	/// ���ӁF�R�s�[���Ɠ����q�m�[�h���Q�Ƃ���
	/// </summary>
	/// <param name=""></param>
	Node(const Node&);
	~Node() {}

	/// <summary>
	/// �m�[�h��]������(MCTS�̑I���E�o�b�N�v���p�Q�[�V����)
	/// </summary>
	/// <param name="copy">�ύX���Ă����Ֆ�</param>
	/// <returns>�v���C�A�E�g�̌���</returns>
	double Evaluate(BitBoard* copy);

	/// <summary>
	/// MCTS�̓W�J
	/// </summary>
	/// <param name="board">�m�[�h�ł̔Ֆʏ��</param>
	void Expand(const BitBoard& board);

	/// <summary>
	/// �q�m�[�h�̒�����I������D
	/// �q�m�[�h���Ȃ��ꍇ��nullptr��Ԃ�
	/// </summary>
	/// <returns>�I�����ꂽ�q�m�[�h</returns>
	Node* SelectChildren() const;
private:
	Point action_;
	double w_;
	double ww_;
	int n_;
	std::vector<Node*> children_;

	double UCB1(int N) const;
	double UCB1_Tuned(int N) const;
};
