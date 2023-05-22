#pragma once
#include "Player.hpp"
#include "Point/Point.hpp"
#include "Allocator/Allocator.hpp"
#include "Random.hpp"
#include "Timer/Timer.hpp"
#include "Node.hpp"

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
	MCTS(int num_nodes, std::chrono::milliseconds::rep search_time);
	void Init() override;
	Point Act(const BitBoard& board) override;

	/// <summary>
	/// 平均プレイアウト回数を返す（小数点以下切り捨て）
	/// </summary>
	/// <returns>平均プレイアウト回数</returns>
	int AveragePlayout() const;

	/// <summary>
	/// 探索時間の取得
	/// </summary>
	/// <returns>1ターン当たりの探索時間[ms]</returns>
	std::chrono::milliseconds::rep GetSearchTime() const;
private:
	const std::chrono::milliseconds::rep SEARCH_TIME_;
	Allocator<Node> allocator_;
	Random random_;
	int sum_playout_;
	int turn_playout_;
};