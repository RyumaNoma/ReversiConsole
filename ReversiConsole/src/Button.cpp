#include "Button.hpp"
#include "DxLib.h"
// ”Ä—p
#include "GameFunction.hpp"

Button::Button(int x1, int y1, int x2, int y2, std::string text, unsigned int background_color, unsigned int text_color, int font_size)
	: x1_(x1)
	, y1_(y1)
	, x2_(x2)
	, y2_(y2)
	, text_(text)
	, background_color_(background_color)
	, text_color_(text_color)
	, font_size_(font_size)
{
}

void Button::Draw() const
{
	const auto [TextLeft, TextTop] = GameFunction::GetLeftTopToAlignCenter(x1_, y1_, x2_, y2_, text_, font_size_);

	DrawBox(x1_, y1_, x2_, y2_, background_color_, 1);
	SetFontSize(font_size_);
	DrawString(TextLeft, TextTop, text_.c_str(), text_color_);
}

bool Button::IsPressed() const
{
	const bool Clicked = (GetMouseInput() & MOUSE_INPUT_LEFT);
	int mouse_x, mouse_y;
	GetMousePoint(&mouse_x, &mouse_y);
	const bool IsInsideButton = (x1_ <= mouse_x && mouse_x <= x2_ && y1_ <= mouse_y && mouse_y <= y2_);
	return (Clicked && IsInsideButton);
}
