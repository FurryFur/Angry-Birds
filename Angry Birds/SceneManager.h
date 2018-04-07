#pragma once

#include <unordered_map>
#include "Scene.h"

class SceneManager
{
public:
	SceneManager();
	~SceneManager();
	Scene* getCurrentScene() const;
	void addScene(std::unique_ptr<Scene>, std::string);
	void loadNewScene(std::string);

private:
	Scene* m_currentScene;
	std::unordered_map<std::string, std::unique_ptr<Scene>> m_sceneMap;
};

