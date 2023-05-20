#pragma once
#include <map>
#include <string>
class SceneManager;

class Scene
{
public:
	Scene(SceneManager* manager) : manager_(manager) {}
	virtual ~Scene() = default;
	virtual void OnChanged(const std::map<std::string, int>& param) = 0;
	virtual void Draw() const = 0;
	virtual void Update() = 0;

	static constexpr int FRAMES_PER_SECOND = 30;
protected:
	SceneManager* manager_;
};

