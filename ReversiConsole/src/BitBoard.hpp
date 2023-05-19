#pragma once
#include <cstdint>
#include <iostream>
#include <functional>
#include <vector>

class Point;

class BitBoard
{
private:
	using Board = std::uint64_t;
	using ShiftFunc = std::function<Board(Board, unsigned int)>;
	static const Board kHorizontalEdge;
	static const Board kVerticalEdge;
	static const Board kDiagonalEdge;
private:
	// [0] ... me
	// [1] ... opponent
	std::uint64_t board_[2];
private:
	/// <summary>
	/// 左シフト演算を行う
	/// </summary>
	/// <param name="a">シフトされる値</param>
	/// <param name="b">シフトするビット数</param>
	/// <returns>aをbだけ左シフトした値</returns>
	static Board shl(Board a, std::uint32_t b);

	/// <summary>
	/// 右シフト演算を行う
	/// </summary>
	/// <param name="a">シフトされる値</param>
	/// <param name="b">シフトするビット数</param>
	/// <returns>aをbだけ右シフトした値</returns>
	static Board shr(Board a, std::uint32_t b);

	/// <summary>
	/// meの石から連続するopponentの石を盤面形式で求める.
	/// 開始位置が複数ある場合でも正しく動作する．
	/// 返されるデータに開始地点と連続する7つ目のマスが含まれないことに注意．
	/// </summary>
	/// <param name="me">自分の盤面</param>
	/// <param name="mask">(盤面の端を表すマスク) and (敵の盤面)</param>
	/// <param name="shift">shif(a,b) = aをbビットシフトする関数</param>
	/// <param name="n">シフトするビット数</param>
	/// <returns>meの石から連続するopponentの石を1とする盤面</returns>
	static Board Line(Board me, Board mask, ShiftFunc shift, int n);

	/// <summary>
	/// me側の合法手を盤面形式で求める
	/// </summary>
	/// <param name="me">自分の盤面</param>
	/// <param name="opponent">敵の盤面</param>
	/// <returns>me側の合法手を1とする盤面</returns>
	static Board Legal(Board me, Board opponent);

	/// <summary>
	/// 反転する石を求める
	/// </summary>
	/// <param name="me">自分の盤面</param>
	/// <param name="opponent">敵の盤面</param>
	/// <param name="point">me側が石を置く場所</param>
	/// <returns>反転する石を1とする盤面</returns>
	static Board ReverseStones(Board me, Board opponent, Board position);

	/// <summary>
	/// actionで設置した石による反転をboard_に反映させる．
	/// 石の設置も行う
	/// </summary>
	/// <param name="action">行動の内容</param>
	void Reverse(Point action);
public:
	BitBoard();
	BitBoard(const BitBoard& bit_board);

	/// <summary>
	/// 盤面の初期化．
	/// 4つの石を置く
	/// </summary>
	void Init();

	/// <summary>
	/// 行動を盤面に反映させる．
	/// その行動が合法手であるかの判定も行う
	/// </summary>
	/// <param name="action">行動の内容</param>
	/// <returns>actionが合法手の場合のみtrue</returns>
	bool Act(Point action);

	/// <summary>
	/// 置かれた石の数を数える
	/// </summary>
	/// <param name="is_opponent">数える側のプレイヤーが敵側ならtrue</param>
	/// <returns>置かれた石の数</returns>
	int CountStones(bool is_opponent) const;

	/// <summary>
	/// 試合の終了判定．片方がパスしても試合は続く
	/// </summary>
	/// <returns>試合が終了していたらtrue，それ以外はfalse</returns>
	bool IsFinish() const;

	/// <summary>
	/// その盤面に対して合法手の有無を調べる
	/// </summary>
	/// <param name="player_side">確認を行う側のプレイヤー</param>
	/// <returns>合法手が一つでもあるならtrue</returns>
	bool IsExistLegal() const;

	/// <summary>
	/// Legalのラッパー関数
	/// </summary>
	/// <param name="player_side">自分</param>
	/// <returns>合法手を1とする盤面</returns>
	Board LegalPublic() const;

	/// <summary>
	/// 自分側プレイヤーの合法手を列挙する
	/// </summary>
	/// <returns>自分側プレイヤーの合法手</returns>
	std::vector<Point> LegalActions() const;

	/// <summary>
	/// 盤面の自分側と敵側のコマを入れ替える
	/// </summary>
	void Swap();

	/// <summary>
	/// 試合の結果を判定する
	/// 前提条件：試合が終了していること
	/// </summary>
	/// <returns>勝ち：1, 引き分け：0.5, 負け：0</returns>
	double Result() const;

	bool operator==(const BitBoard& bitboard) const;
	bool operator!=(const BitBoard& bitboard) const;

	friend std::ostream& operator<<(std::ostream& os, const BitBoard& bit_board);
	friend class MatchScene;
};

