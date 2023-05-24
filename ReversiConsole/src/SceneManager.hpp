#pragma once
#include <string>
#include <map>
#include <queue>
#include <chrono>
#include "Scene.hpp"

class SceneManager
{
public:
	SceneManager();
	~SceneManager() {}

	/// <summary>
	/// 毎フレーム呼び出す．
	/// 現在のシーンのDrawとUpdateを呼び出す
	/// </summary>
	/// <returns>正常に終了したらtrue</returns>
	bool Update();

	/// <summary>
	/// 管理するシーン群にシーンを追加する
	/// </summary>
	/// <param name="scene_name">シーン名</param>
	/// <param name="scene">シーン</param>
	/// <returns>正常に終了したらtrue</returns>
	bool Add(std::string scene_name, Scene* scene);

	/// <summary>
	/// 最初に起動したときに呼び出されるシーンを設定する
	/// </summary>
	/// <param name="scene_name">スタートアップシーン</param>
	/// <returns>通常に終了したらtrue</returns>
	bool SetStartUpScene(std::string scene_name);

	/// <summary>
	/// 次のフレームから呼び出すシーンを変更する．
	/// 一般的に，シーンクラス側から呼び出される．
	/// </summary>
	/// <param name="scene_name">設定するシーン</param>
	/// <param name="tell_game_data">次のシーンに伝えるゲームデータ</param>
	/// <returns>通常に終了したらtrue</returns>
	bool Change(std::string scene_name, const std::map<std::string, int>& tell_game_data);

	/// <summary>
	/// 管理しているシーン群が空かを判定する
	/// </summary>
	/// <returns>シーン群が空ならtrue</returns>
	bool Empty() const;

	/// <summary>
	/// Exit()を呼び出した次のフレームからoperator bool()がfalseを返すようになる
	/// </summary>
	void Exit();

	/// <summary>
	/// 管理しているシーンの個数を求める
	/// </summary>
	/// <returns>管理しているシーンの個数</returns>
	size_t Size() const;

	operator bool() const;
private:
	std::map<std::string, Scene*> scenes_;
	std::string startup_scene_;
	std::string now_scene_;//TODO: Scene*型に変更する
	bool changed_;
	std::map<std::string, int> game_data_;
	bool valid_exec_;
	std::queue<std::chrono::system_clock::time_point> frame_time_queue_;
};