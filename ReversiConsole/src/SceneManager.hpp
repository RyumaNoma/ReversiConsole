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
	bool Change(std::string scene_name, const std::map<std::string, int>& tell_game_data);
	bool Empty() const;
	/// <summary>
	/// Exit()を呼び出した次のフレームからoperator bool()がfalseを返すようになる
	/// </summary>
	void Exit();
	size_t Size() const;

	operator bool() const;
private:
	std::map<std::string, Scene*> scenes_;
	std::string startup_scene_;
	std::string now_scene_;//TODO: Scene*型に変更する
	bool changed_;
	std::map<std::string, int> game_data_;
	bool valid_exec_;
};