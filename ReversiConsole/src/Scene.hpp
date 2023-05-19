#pragma once
#include <map>
#include <string>

class Scene
{
public:
	Scene() {}
	virtual ~Scene() = default;
	virtual void OnChanged(const std::map<std::string, int>& param) = 0;
	virtual void Draw() const = 0;
	virtual void Update() = 0;
private:
};

