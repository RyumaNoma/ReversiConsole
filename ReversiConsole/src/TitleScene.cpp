#include "TitleScene.hpp"
#include "DxLib.h"
// シーン関連
#include "SceneManager.hpp"
// 汎用
#include "GameFunction.hpp"
#include "Color.hpp"

void TitleScene::OnChanged(const std::map<std::string, int>& param)
{
}

void TitleScene::Draw() const
{
	// 画面サイズの取得
	auto [width, height] = GameFunction::GetWindowSize();
	const int TitleFontSize = static_cast<int>(height * 0.1);
	const int NormalFontSize = static_cast<int>(height * 0.08);

	DrawBox(0, 0, width, height, Color::TITLE_BACKGROUND, true);
	SetFontSize(TitleFontSize);
	DrawString(0, 0, "Reversi", Color::GAME_TITLE);
	SetFontSize(NormalFontSize);
	DrawString(0, TitleFontSize, "-Press Enter key to start-", Color::TITLE_EXPLAIN_KEY_CHAR);
	DrawString(0, TitleFontSize + NormalFontSize, "-Press Q key to start-", Color::TITLE_EXPLAIN_KEY_CHAR);
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
