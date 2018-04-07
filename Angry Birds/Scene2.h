#pragma once

#include "Scene.h"

#include <memory>

class Scene2 : public Scene
{
public:
	Scene2(SceneManager&);
	~Scene2() override;

	std::unique_ptr<Scene> createNew() const override;
};

