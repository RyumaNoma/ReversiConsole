#pragma once
#include "Player.hpp"
#include "Point/Point.hpp"
#include "Allocator/Allocator.hpp"
#include "Random.hpp"
#include "Timer/Timer.hpp"
class Node;

/// <summary>
/// モンテカルロ木探索をするプレイヤー
/// 
/// 改良の余地
/// ・探索係数Cの動的変化
/// ・ターン間の探索木の継続
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