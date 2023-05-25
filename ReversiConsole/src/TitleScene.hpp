#pragma once
#include "Scene.hpp"
// UIŠÖ˜A
#include "Button.hpp"

class TitleScene
	: public Scene
{
public:
	TitleScene(SceneManager* manager);
	virtual void OnChanged(const std::map<std::string, int>& param) override;
	virtual void Draw() const override;
	virtual void Update() override;
private:
	int width_, height_;
	int title_font_size_;
	int normal_font_size_;
	Button match_btn_;
	Button exit_btn_;
};