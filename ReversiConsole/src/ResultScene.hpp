#pragma once
#include "Scene.hpp"

class ResultScene
	: public Scene
{
public:
	ResultScene(SceneManager* manager) : Scene(manager) {}

	virtual void OnChanged(const std::map<std::string, int>& param) override;

	virtual void Draw() const override;

	virtual void Update() override;

};