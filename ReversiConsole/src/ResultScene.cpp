#include "ResultScene.hpp"
#include "DxLib.h"
// シーン関連
#include "SceneManager.hpp"
// 汎用
#include "Color.hpp"
#include "GameFunction.hpp"

ResultScene::ResultScene(SceneManager* manager)
	: level_(0)
	, human_result_(0)
	, human_stones_(0)
	, ai_stones_(0)
	, width_(0)
	, height_(0)
	, title_font_size_(0)
	, normal_font_size_(0)
	, title_btn_()
	, exit_btn_()
	, Scene(manager)
{
}

void ResultScene::OnChanged(const std::map<std::string, int>& param)
{
	level_ = param.at("Level");
	human_result_ = param.at("HumanResult");
	human_stones_ = param.at("NumberHumanStones");
	ai_stones_ = param.at("NumberAIStones");

	auto window_size = GameFunction::GetWindowSize();
	width_ = window_size.first;
	height_ = window_size.second;
	title_font_size_ = static_cast<int>(height_ * 0.1);
	normal_font_size_ = static_cast<int>(height_ * 0.08);
	const int Mergin = 10;
	const int ButtonWidth = (width_ - 3 * Mergin) / 2;
	const int ButtonTop = title_font_size_ + normal_font_size_ * 3 + Mergin;
	const int ButtonBottom = ButtonTop + normal_font_size_ + Mergin;

	title_btn_ = Button(
		Mergin,
		ButtonTop,
		Mergin + ButtonWidth,
		ButtonBottom,
		"タイトルに戻る",
		Color::BUTTON_BACKGROUND,
		Color::BUTTON_CHAR,
		normal_font_size_
	);

	exit_btn_ = Button(
		Mergin * 2 + ButtonWidth,
		ButtonTop,
		Mergin * 2 + ButtonWidth * 2,
		ButtonBottom,
		"ゲーム終了",
		Color::BUTTON_BACKGROUND,
		Color::BUTTON_CHAR,
		normal_font_size_
	);
}

void ResultScene::Draw() const
{	
	SetFontSize(title_font_size_);
	DrawString(0, 0, "対戦結果", Color::RESULT_TITLE_CHAR);
	SetFontSize(normal_font_size_);
	// 勝敗
	switch (human_result_)
	{
	case 1:
		DrawString(0, title_font_size_, "勝利！", Color::RESULT_WIN_CHAR);
		break;
	case 0:
		DrawString(0, title_font_size_, "引き分け", Color::RESULT_DRAW_CHAR);
		break;
	case -1:
		DrawString(0, title_font_size_, "敗北 ...", Color::RESULT_LOSE_CHAR);
		break;
	default:
		break;
	}
	// 石の数
	DrawFormatString(0, title_font_size_ + normal_font_size_, Color::RESULT_STONES_CHAR,     "あなた: %d 石", human_stones_);
	DrawFormatString(0, title_font_size_ + normal_font_size_ * 2, Color::RESULT_STONES_CHAR, "    AI: %d 石", ai_stones_);
	// ボタン
	title_btn_.Draw();
	exit_btn_.Draw();
}

void ResultScene::Update()
{
	if (title_btn_.IsPressed())
	{
		manager_->Change("Title", std::map<std::string, int>());
	}
	if (exit_btn_.IsPressed())
	{
		manager_->Exit();
	}
}
