#include "SceneManager.h"



SceneManager::SceneManager()
	: m_currentScene(nullptr)
{
}


SceneManager::~SceneManager()
{
}

Scene* SceneManager::getCurrentScene() const
{
	return m_currentScene;
}

void SceneManager::addScene(std::unique_ptr<Scene> newScene)
{
	if (!m_currentScene)
		m_currentScene = newScene.get();

	m_sceneList.push_back(std::move(newScene));
}
