#pragma once
#include "Scene.hpp"
#include "BitBoard.hpp"
class Player;
class SceneManager;

// TODO: とにかくMatchSceneクラスを完成させる
// TODO: コメント整備
class MatchScene
	: public Scene
{
public:
	enum class MatchState
	{
		BeforeMatch,
		Think,
		PlayAnimation
	};
public:
	MatchScene(SceneManager* manager);
	~MatchScene() = default;
	void OnChanged(const std::map<std::string, int>& param) override;
	void Draw() const override;
	void Update() override;

	/// <summary>
	/// 変数を初期化する．
	/// 毎試合前に呼び出す
	/// </summary>
	void Init();

	/// <summary>
	/// 先手と後手のプレイヤーをそれぞれ設定する．
	/// </summary>
	/// <param name="first_player">先手のプレイヤー</param>
	/// <param name="second_player">後手のプレイヤー</param>
	void SetPlayers(Player* first_player, Player* second_player);

	/// <summary>
	/// 人間側からみた結果を求める．
	/// 前提条件：試合が終了していること
	/// </summary>
	/// <returns>(勝ち：1)(引き分け：0)(負け：-1)</returns>
	int HumanResult() const;

	/// <summary>
	/// 現時点での人間側の石の数を求める
	/// </summary>
	/// <returns>人間側の石の数</returns>
	int HumanStones() const;

	/// <summary>
	/// 現時点でのAI側の石の数を求める
	/// </summary>
	/// <returns>AI側の石の数</returns>
	int AIStones() const;

	// サブ更新関数
	void UpdateBeforeMatch();
	void UpdateThink();
	void UpdatePlayAnimation();

	// サブ描画関数
	void DrawBeforeMatch() const;
	void DrawThink() const;
	void DrawPlayAnimation() const;
	void DrawBoard(int window_width, int window_height) const;
private:
	BitBoard last_board_;
	BitBoard board_;
	Player* player_[2];
	int turn_;// 0-indexed
	int count_frame_;
	MatchState state_;
	int human_side_;
	bool is_pass_;
};