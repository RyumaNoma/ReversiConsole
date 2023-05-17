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
	/// <param name=""></param>
	Node(const Node&);
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
private:
	Point action_;
	double w_;
	double ww_;
	int n_;
	std::vector<Node*> children_;

	double UCB1(int N) const;
	double UCB1_Tuned(int N) const;
};
