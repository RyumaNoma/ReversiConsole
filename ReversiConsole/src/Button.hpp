#pragma once
#include <string>

class Button
{
public:
	Button(int x1, int y1, int x2, int y2, std::string text, unsigned int background_color, unsigned int char_color, int font_size);
	Button(const Button&) = default;
	~Button() = default;

	void Draw() const;
	bool IsPressed() const;
private:
	unsigned int background_color_;
	unsigned int text_color_;
	int x1_, y1_, x2_, y2_;
	std::string text_;
	int font_size_;
};