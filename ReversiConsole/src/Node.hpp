#pragma once
#include "Point/Point.hpp"
#include <vector>

class BitBoard;

class Node
{
public:
	Node();
	/// <summary>
	/// 注意：コピー元と同じ子ノードを参照する
	/// </summary>
	/// <param name="node">コピー元</param>
	Node(const Node& node);
	~Node() {}

	/// <summary>
	/// ノードを評価する(MCTSの選択・バックプロパゲーション)
	/// </summary>
	/// <param name="copy">変更していい盤面</param>
	/// <returns>プレイアウトの結果</returns>
	double Evaluate(BitBoard* copy);

	/// <summary>
	/// MCTSの展開
	/// </summary>
	/// <param name="board">ノードでの盤面状態</param>
	void Expand(const BitBoard& board);

	/// <summary>
	/// 子ノードの中から選択する．
	/// 子ノードがない場合はnullptrを返す
	/// </summary>
	/// <returns>選択された子ノード</returns>
	Node* SelectChildren() const;

	/// <summary>
	/// もっともよい行動を求める．
	/// 正確には，子ノードの中から最も訪問回数が多い子ノードの行動
	/// </summary>
	/// <returns>もっともよい行動</returns>
	Point SelectBestAction() const;

	friend std::ostream& operator<<(std::ostream& os, const Node& node);
private:
	Point action_;
	double w_;
	double ww_;
	int n_;
	std::vector<Node*> children_;

	/// <summary>
	/// UCB1を計算する
	/// </summary>
	/// <param name="N">親ノードの実行回数</param>
	/// <param name="C">探索係数</param>
	/// <returns>UCB1の値</returns>
	double UCB1(int N, double C) const;

	/// <summary>
	/// UCB1_Tunedを計算する
	/// </summary>
	/// <param name="N">親ノードの実行回数</param>
	/// <param name="C">探索係数</param>
	/// <returns>UCB1_Tunedの値</returns>
	double UCB1_Tuned(int N, double C) const;
};
