#include "TitleScene.hpp"
#include "DxLib.h"
// シーン関連
#include "SceneManager.hpp"
// UI関連
#include "Button.hpp"
// 汎用
#include "GameFunction.hpp"
#include "Color.hpp"

TitleScene::TitleScene(SceneManager* manager)
	: width_(0)
	, height_(0)
	, title_font_size_(0)
	, normal_font_size_(0)
	, match_btn_()
	, exit_btn_()
	, Scene(manager)
{
}

void TitleScene::OnChanged(const std::map<std::string, int>& param)
{
	// 画面サイズの取得
	auto window_size = GameFunction::GetWindowSize();
	width_ = window_size.first;
	height_ = window_size.second;
	title_font_size_ = static_cast<int>(height_ * 0.1);
	normal_font_size_ = static_cast<int>(height_ * 0.08);
	const int Mergin = 10;
	const int ButtonWidth = (width_ - 3 * Mergin) / 2;
	const int ButtonTop = title_font_size_ + Mergin;
	const int ButtonBottom = ButtonTop + normal_font_size_ + Mergin;

	match_btn_ = Button(
		Mergin,
		ButtonTop,
		Mergin + ButtonWidth,
		ButtonBottom,
		"対戦開始",
		Color::BUTTON_BACKGROUND,
		Color::BUTTON_CHAR,
		normal_font_size_);
	
	exit_btn_ = Button(
		Mergin * 2 + ButtonWidth,
		ButtonTop,
		Mergin * 2 + ButtonWidth * 2,
		ButtonBottom,
		"ゲーム終了",
		Color::BUTTON_BACKGROUND,
		Color::BUTTON_CHAR,
		normal_font_size_);
}

void TitleScene::Draw() const
{
	DrawBox(0, 0, width_, height_, Color::TITLE_BACKGROUND, true);
	SetFontSize(title_font_size_);
	DrawString(0, 0, "Reversi", Color::GAME_TITLE);
	SetFontSize(normal_font_size_);
	match_btn_.Draw();
	exit_btn_.Draw();
}

void TitleScene::Update()
{
	if (match_btn_.IsPressed())
	{
		manager_->Change("Match", std::map<std::string, int>());
	}
	if (exit_btn_.IsPressed())
	{
		manager_->Exit();
	}
}
