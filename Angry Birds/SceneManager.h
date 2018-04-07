#pragma once

#include "Scene.h"

class SceneManager
{
public:
	SceneManager();
	~SceneManager();
	Scene* getCurrentScene() const;
	void addScene(std::unique_ptr<Scene>);

private:
	Scene* m_currentScene;
	std::vector<std::unique_ptr<Scene>> m_sceneList;
};

