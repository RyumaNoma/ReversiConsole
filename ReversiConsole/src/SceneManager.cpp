#include "SceneManager.hpp"

SceneManager::SceneManager()
	: scenes_()
	, startup_scene_()
	, now_scene_()
	, game_data_()
	, changed_(true)
	, valid_exec_(true)
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
		Scene* scene = scenes_.at(now_scene_);
		// TODO: マルチスレッド化してロード画面の実装
		if (changed_)
		{
			scene->OnChanged(game_data_);
			changed_ = false;
		}
		scene->Draw();
		scene->Update();
		return true;
	}
	return false;
}

bool SceneManager::Add(std::string scene_name, Scene* scene)
{
	if (scenes_.count(scene_name))
	{
		return false;
	}
	scenes_.insert(std::make_pair(scene_name, scene));
	return true;
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

bool SceneManager::Change(std::string scene_name, const std::map<std::string, int>& tell_game_data)
{
	if (scenes_.count(scene_name))
	{
		game_data_ = tell_game_data;
		now_scene_ = scene_name;
		changed_ = true;
		return true;
	}
	return false;
}

bool SceneManager::Empty() const
{
	return scenes_.empty();
}

void SceneManager::Exit()
{
	valid_exec_ = false;
}

size_t SceneManager::Size() const
{
	return scenes_.size();
}

SceneManager::operator bool() const
{
	return valid_exec_;
}
