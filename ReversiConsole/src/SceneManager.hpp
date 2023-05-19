#pragma once
#include <string>
#include <map>
#include "Scene.hpp"

class SceneManager
{
public:
	SceneManager();
	~SceneManager() {}
	bool Update();
	bool Add(std::string scene_name, Scene* scene);
	bool SetStartUpScene(std::string scene_name);
	bool Empty() const;
	size_t Size() const;
private:
	std::map<std::string, Scene*> scenes_;
	std::string startup_scene_;
	std::string now_scene_;
};