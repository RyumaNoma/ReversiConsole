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
	/// <param name="node">�R�s�[��</param>
	Node(const Node& node);
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

	/// <summary>
	/// �����Ƃ��悢�s�������߂�D
	/// ���m�ɂ́C�q�m�[�h�̒�����ł��K��񐔂������q�m�[�h�̍s��
	/// </summary>
	/// <returns>�����Ƃ��悢�s��</returns>
	Point SelectBestAction() const;

	friend std::ostream& operator<<(std::ostream& os, const Node& node);
private:
	Point action_;
	double w_;
	double ww_;
	int n_;
	std::vector<Node*> children_;

	/// <summary>
	/// UCB1���v�Z����
	/// </summary>
	/// <param name="N">�e�m�[�h�̎��s��</param>
	/// <param name="C">�T���W��</param>
	/// <returns>UCB1�̒l</returns>
	double UCB1(int N, double C) const;

	/// <summary>
	/// UCB1_Tuned���v�Z����
	/// </summary>
	/// <param name="N">�e�m�[�h�̎��s��</param>
	/// <param name="C">�T���W��</param>
	/// <returns>UCB1_Tuned�̒l</returns>
	double UCB1_Tuned(int N, double C) const;
};
