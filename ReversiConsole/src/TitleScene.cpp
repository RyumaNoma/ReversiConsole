#include "TitleScene.hpp"
#include "DxLib.h"
#include "SceneManager.hpp"

void TitleScene::OnChanged(const std::map<std::string, int>& param)
{
}

void TitleScene::Draw() const
{
	// 画面サイズの取得
	RECT rc;
	GetWindowRect(GetDesktopWindow(), &rc);
	int width = rc.right - rc.left;
	int height = rc.bottom - rc.top;

	DrawBox(rc.left, rc.top, rc.right, rc.bottom, GetColor(255, 192, 203), true);
	SetFontSize(100);
	DrawString(0, 0, "Reversi", GetColor(255, 255, 255));
	SetFontSize(80);
	DrawString(0, 100, "-Press space key to start-", GetColor(255, 255, 255));
}

void TitleScene::Update()
{
	if (CheckHitKey(KEY_INPUT_SPACE))
	{
		manager_->Change("Match", std::map<std::string, int>());
	}
}
