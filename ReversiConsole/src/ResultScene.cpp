#include "ResultScene.hpp"
#include "SceneManager.hpp"
#include "DxLib.h"

void ResultScene::OnChanged(const std::map<std::string, int>& param)
{
}

void ResultScene::Draw() const
{
	// プレイヤー？の勝利！
	// コマの数
	// 悪手・いい手
	// Press space to title
}

void ResultScene::Update()
{
	if (CheckHitKey(KEY_INPUT_SPACE))
	{
		manager_->Change("Match", std::map<std::string, int>());
	}
}
