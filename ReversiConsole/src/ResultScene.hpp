#pragma once
#include "Scene.hpp"

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
};