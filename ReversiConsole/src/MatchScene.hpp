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
	MatchScene(SceneManager* manager);
	~MatchScene() = default;
	void OnChanged(const std::map<std::string, int>& param) override;
	void Draw() const override;
	void Update() override;
	
	void BeforeMatch();
	void Think();
	void PlayAnimation();
	
	void Init();
	void SetPlayers(Player* first_player, Player* second_player);

	// 描画
	void DrawBeforeMatch() const;
	void DrawThink() const;
	void DrawPlayAnimation() const;
	void DrawAfterMatch() const;
	void DrawBoard(int window_width, int window_height) const;
	
	enum class MatchState
	{
		BeforeMatch,
		Think,
		PlayAnimation,
		AfterMatch
	};
private:
	BitBoard last_board_;
	BitBoard board_;
	Player* player_[2];
	int turn_;// 0-indexed
	int count_frame_;
	MatchState state_;
};