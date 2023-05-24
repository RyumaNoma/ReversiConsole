#include "TitleScene.hpp"
#include "DxLib.h"
#include "SceneManager.hpp"
#include "GameFunction.hpp"
#include "Color.hpp"

void TitleScene::OnChanged(const std::map<std::string, int>& param)
{
}

void TitleScene::Draw() const
{
	// ‰æ–ÊƒTƒCƒY‚ÌŽæ“¾
	auto [width, height] = GameFunction::GetWindowSize();

	DrawBox(0, 0, width, height, Color::TITLE_BACKGROUND, true);
	SetFontSize(100);
	DrawString(0, 0, "Reversi", Color::GAME_TITLE);
	SetFontSize(80);
	DrawString(0, 100, "-Press Enter key to start-", Color::TITLE_EXPLAIN_KEY_CHAR);
	DrawString(0, 180, "-Press Q key to start-", Color::TITLE_EXPLAIN_KEY_CHAR);
}

void TitleScene::Update()
{
	if (CheckHitKey(KEY_INPUT_RETURN))
	{
		manager_->Change("Match", std::map<std::string, int>());
	}
	if (CheckHitKey(KEY_INPUT_Q))
	{
		manager_->Exit();
	}
}
