#pragma once
#include "Player.hpp"
#include "Point/Point.hpp"
#include "Allocator/Allocator.hpp"
#include "Random.hpp"
#include "Timer/Timer.hpp"
class Node;

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
	MCTS(int num_nodes, double C, int expand_thresold, std::chrono::milliseconds::rep search_time);
	void Init() override;
	Point Act(const BitBoard& board) override;
private:
	const std::chrono::milliseconds::rep SEARCH_TIME_;
	Allocator<Node> allocator_;
	Random random_;
};