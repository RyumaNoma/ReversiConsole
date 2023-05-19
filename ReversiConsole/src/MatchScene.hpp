#pragma once
#include "Scene.hpp"
#include "BitBoard.hpp"
class Player;

class MatchScene
	: public Scene
{
public:
	MatchScene();
	MatchScene(Player* player1, Player* player2);
	~MatchScene() = default;
	void OnChanged(const std::map<std::string, int>& param) override;
	void Draw() const override;
	void Update() override;

	void Init();

	// •`‰æ
	void DrawBoard(int window_width, int window_height) const;
private:
	BitBoard board_;
	Player* player[2];
	int turn_;// 0-indexed
};