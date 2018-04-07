#pragma once

#include "Scene.h"

#include <memory>

class Scene1 : public Scene
{
public:
	Scene1(SceneManager&);
	~Scene1() override;

	std::unique_ptr<Scene> createNew() const override;
};

