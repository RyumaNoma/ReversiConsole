#include "ResultScene.hpp"
#include "DxLib.h"
// �V�[���֘A
#include "SceneManager.hpp"
// �ėp
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
		"�^�C�g���ɖ߂�",
		Color::BUTTON_BACKGROUND,
		Color::BUTTON_CHAR,
		normal_font_size_
	);

	exit_btn_ = Button(
		Mergin * 2 + ButtonWidth,
		ButtonTop,
		Mergin * 2 + ButtonWidth * 2,
		ButtonBottom,
		"�Q�[���I��",
		Color::BUTTON_BACKGROUND,
		Color::BUTTON_CHAR,
		normal_font_size_
	);
}

void ResultScene::Draw() const
{	
	SetFontSize(title_font_size_);
	DrawString(0, 0, "�ΐ팋��", Color::RESULT_TITLE_CHAR);
	SetFontSize(normal_font_size_);
	// ���s
	switch (human_result_)
	{
	case 1:
		DrawString(0, title_font_size_, "�����I", Color::RESULT_WIN_CHAR);
		break;
	case 0:
		DrawString(0, title_font_size_, "��������", Color::RESULT_DRAW_CHAR);
		break;
	case -1:
		DrawString(0, title_font_size_, "�s�k ...", Color::RESULT_LOSE_CHAR);
		break;
	default:
		break;
	}
	// �΂̐�
	DrawFormatString(0, title_font_size_ + normal_font_size_, Color::RESULT_STONES_CHAR,     "���Ȃ�: %d ��", human_stones_);
	DrawFormatString(0, title_font_size_ + normal_font_size_ * 2, Color::RESULT_STONES_CHAR, "    AI: %d ��", ai_stones_);
	// �{�^��
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
