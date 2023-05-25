#pragma once
#include "Scene.hpp"
#include "Button.hpp"

class ResultScene
	: public Scene
{
public:
	ResultScene(SceneManager* manager);
	virtual void OnChanged(const std::map<std::string, int>& param) override;
	virtual void Draw() const override;
	virtual void Update() override;
private:
	int level_;
	int human_result_;
	int human_stones_;
	int ai_stones_;

	int width_, height_;
	int title_font_size_;
	int normal_font_size_;
	Button title_btn_;
	Button exit_btn_;
};