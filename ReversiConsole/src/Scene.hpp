#pragma once
#include <map>
#include <string>
class SceneManager;

class Scene
{
public:
	Scene(SceneManager* manager) : manager_(manager) {}
	virtual ~Scene() = default;

	/// <summary>
	/// シーンが自身に切り替わった最初のフレームの最初に呼び出される
	/// </summary>
	/// <param name="param">前のシーンから渡された情報</param>
	virtual void OnChanged(const std::map<std::string, int>& param) = 0;

	/// <summary>
	/// 毎フレーム呼び出される描画用関数
	/// </summary>
	virtual void Draw() const = 0;

	/// <summary>
	/// 毎フレーム呼び出される更新用関数．
	/// </summary>
	virtual void Update() = 0;

	static constexpr int FRAMES_PER_SECOND = 30;
protected:
	SceneManager* manager_;
};

