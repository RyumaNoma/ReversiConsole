#include "SceneManager.hpp"
#include "DxLib.h"

SceneManager::SceneManager()
	: scenes_()
	, startup_scene_()
	, now_scene_(nullptr)
	, game_data_()
	, changed_(true)
	, valid_exec_(true)
	, frame_time_queue_()
{
}

bool SceneManager::Update()
{
	// FPSŒv‘ª
	auto now = std::chrono::system_clock::now();
	frame_time_queue_.push(now);
	while (std::chrono::duration_cast<std::chrono::milliseconds>(now - frame_time_queue_.front()).count() > 1000)
	{
		frame_time_queue_.pop();
	}
	//printfDx("%d\n", static_cast<int>(frame_time_queue_.size()));

	if (now_scene_ == nullptr)
	{
		if (startup_scene_ == "") return false;
		if (!scenes_.count(startup_scene_)) return false;
		now_scene_ = scenes_.at(startup_scene_);
	}

	if (now_scene_)
	{
		if (changed_)
		{
			now_scene_->OnChanged(game_data_);
			changed_ = false;
		}
		now_scene_->Draw();
		ScreenFlip();
		now_scene_->Update();
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
		now_scene_ = scenes_.at(scene_name);
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
