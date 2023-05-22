#pragma once
#include "Player.hpp"
#include "Point/Point.hpp"
#include "Allocator/Allocator.hpp"
#include "Random.hpp"
#include "Timer/Timer.hpp"
#include "Node.hpp"

/// <summary>
/// �����e�J�����ؒT��������v���C���[
/// 
/// ���ǂ̗]�n
/// �E�T���W��C�̓��I�ω�
/// �E�^�[���Ԃ̒T���؂̌p��
/// </summary>
class MCTS
	: public Player
{
public:
	MCTS();
	MCTS(int num_nodes, std::chrono::milliseconds::rep search_time);
	void Init() override;
	Point Act(const BitBoard& board) override;

	/// <summary>
	/// ���σv���C�A�E�g�񐔂�Ԃ��i�����_�ȉ��؂�̂āj
	/// </summary>
	/// <returns>���σv���C�A�E�g��</returns>
	int AveragePlayout() const;

	/// <summary>
	/// �T�����Ԃ̎擾
	/// </summary>
	/// <returns>1�^�[��������̒T������[ms]</returns>
	std::chrono::milliseconds::rep GetSearchTime() const;
private:
	const std::chrono::milliseconds::rep SEARCH_TIME_;
	Allocator<Node> allocator_;
	Random random_;
	int sum_playout_;
	int turn_playout_;
};