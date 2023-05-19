#pragma once
#include <map>
#include <string>

class Scene
{
public:
	Scene(std::map<std::string, int> param);
	virtual ~Scene() = default;
	virtual void Draw() = 0;
	virtual void Update() = 0;
};

