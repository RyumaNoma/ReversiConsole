#include "SceneManager.hpp"

SceneManager::SceneManager()
	: scenes_()
	, startup_scene_()
	, now_scene_()
{
}

bool SceneManager::Update()
{
	if (now_scene_ == "")
	{
		if (startup_scene_ == "")
		{
			return false;
		}
		else
		{
			now_scene_ = startup_scene_;
		}
	}

	if (scenes_.count(now_scene_))
	{
		scenes_.at(now_scene_)->Draw();
		scenes_.at(now_scene_)->Update();
		return true;
	}
	return false;
}

bool SceneManager::Add(std::string scene_name, Scene* scene)
{
	if (scenes_.count(scene_name))
	{
		scenes_.insert(std::make_pair(scene_name, scene));
		return true;
	}
	return false;
}

bool SceneManager::SetStartUpScene(std::string scene_name)
{
	if (scenes_.count(scene_name))
	{
		startup_scene_ = scene_name;
		return true;
	}
	return false;
}

bool SceneManager::Empty() const
{
	return scenes_.empty();
}

size_t SceneManager::Size() const
{
	return scenes_.size();
}
