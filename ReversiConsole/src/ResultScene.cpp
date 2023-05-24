#include "ResultScene.hpp"
#include "SceneManager.hpp"
#include "DxLib.h"
#include "Color.hpp"

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
	const int NormalFontSize = 100;
	
	SetFontSize(TitleFontSize);
	DrawString(0, 0, "Result", Color::RESULT_TITLE_CHAR);
	SetFontSize(NormalFontSize);
	// Ÿ”s
	switch (human_result_)
	{
	case 1:
		DrawString(0, TitleFontSize, "You Won!", Color::RESULT_WIN_CHAR);
		break;
	case 0:
		DrawString(0, TitleFontSize, "Draw", Color::RESULT_DRAW_CHAR);
		break;
	case -1:
		DrawString(0, TitleFontSize, "You Lost ...", Color::RESULT_LOSE_CHAR);
		break;
	default:
		break;
	}
	// Î‚Ì”
	DrawFormatString(0, TitleFontSize + NormalFontSize, Color::RESULT_STONES_CHAR, "You: %d Stones", human_stones_);
	DrawFormatString(0, TitleFontSize + NormalFontSize * 2, Color::RESULT_STONES_CHAR, " AI: %d Stones", ai_stones_);

	DrawString(0, TitleFontSize + NormalFontSize * 4, "Press space key to go to Title", Color::RESULT_EXPLAIN_KEY_CHAR);
	DrawString(0, TitleFontSize + NormalFontSize * 5, "Press Q to Exit Game", Color::RESULT_EXPLAIN_KEY_CHAR);
}

void ResultScene::Update()
{
	if (CheckHitKey(KEY_INPUT_SPACE))
	{
		manager_->Change("Title", std::map<std::string, int>());
	}
	if (CheckHitKey(KEY_INPUT_Q))
	{
		manager_->Exit();
	}
}
