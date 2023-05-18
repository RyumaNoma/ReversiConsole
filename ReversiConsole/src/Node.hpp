#pragma once
#include "Point/Point.hpp"
#include <vector>
#include "Allocator/Allocator.hpp"

class BitBoard;
class Random;

class Node
{
public:
	Node();
	Node(const Point& action);
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
	double Evaluate(BitBoard& copy, Allocator<Node>& allocator, Random& random);

	/// <summary>
	/// MCTS�̓W�J
	/// </summary>
	/// <param name="board">�m�[�h�ł̔Ֆʏ��</param>
	void Expand(const BitBoard& board, Allocator<Node>& allocator);

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
	friend class NodeUnitTest;
private:
	static constexpr double C_ = 1.0;
	static constexpr int EXPAND_THRESHOLD_ = 1;
	Point action_;
	double w_;
	double ww_;
	int n_;
	std::vector<Node*> children_;

	/// <summary>
	/// UCB1���v�Z����
	/// </summary>
	/// <param name="N">�e�m�[�h�̎��s��</param>
	/// <returns>UCB1�̒l</returns>
	double UCB1(int N) const;

	/// <summary>
	/// UCB1_Tuned���v�Z����
	/// </summary>
	/// <param name="N">�e�m�[�h�̎��s��</param>
	/// <returns>UCB1_Tuned�̒l</returns>
	double UCB1_Tuned(int N) const;
};
