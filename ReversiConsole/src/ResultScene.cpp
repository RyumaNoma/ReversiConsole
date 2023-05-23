#include "ResultScene.hpp"
#include "SceneManager.hpp"
#include "DxLib.h"

ResultScene::ResultScene(SceneManager* manager)
	: level_(0)
	, human_result_(0)
	, human_stones_(0)
	, ai_stones_(0)
	, Scene(manager)
{
}

void ResultScene::OnChanged(const std::map<std::string, int>& param)
{
	level_ = param.at("Level");
	human_result_ = param.at("HumanResult");
	human_stones_ = param.at("NumberHumanStones");
	ai_stones_ = param.at("NumberAIStones");
}

void ResultScene::Draw() const
{
	// Press space to title
	const int TitleFontSize = 300;
	const int NormalFontSize = 200;
	
	SetFontSize(TitleFontSize);
	DrawString(0, 0, "Result", GetColor(255, 255, 255));
	SetFontSize(NormalFontSize);
	// Ÿ”s
	switch (human_result_)
	{
	case 1:
		DrawString(0, TitleFontSize, "You Won!", GetColor(255, 0, 0));
		break;
	case 0:
		DrawString(0, TitleFontSize, "Draw", GetColor(255, 255, 255));
		break;
	case -1:
		DrawString(0, TitleFontSize, "You Lost ...", GetColor(0, 0, 255));
		break;
	default:
		break;
	}
	// Î‚Ì”
	DrawFormatString(0, TitleFontSize + NormalFontSize, GetColor(255, 255, 255), "You: %d Stones", human_stones_);
	DrawFormatString(0, TitleFontSize + NormalFontSize, GetColor(255, 255, 255), " AI: %d Stones", ai_stones_);

	DrawString(0, TitleFontSize + NormalFontSize * 2, "Press space to go to Title", GetColor(255, 255, 255));
}

void ResultScene::Update()
{
	if (CheckHitKey(KEY_INPUT_SPACE))
	{
		manager_->Change("Title", std::map<std::string, int>());
	}
}
