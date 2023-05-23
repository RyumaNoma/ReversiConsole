#include "TitleScene.hpp"
#include "DxLib.h"
#include "SceneManager.hpp"
#include "GameFunction.hpp"

void TitleScene::OnChanged(const std::map<std::string, int>& param)
{
}

void TitleScene::Draw() const
{
	// ‰æ–ÊƒTƒCƒY‚ÌŽæ“¾
	auto [width, height] = GameFunction::GetWindowSize();

	DrawBox(0, 0, width, height, GetColor(255, 192, 203), true);
	SetFontSize(100);
	DrawString(0, 0, "Reversi", GetColor(255, 255, 255));
	SetFontSize(80);
	DrawString(0, 100, "-Press Enter key to start-", GetColor(255, 255, 255));
	DrawString(0, 180, "-Press Q key to start-", GetColor(255, 255, 255));
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
