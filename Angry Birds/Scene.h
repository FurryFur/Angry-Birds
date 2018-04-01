#pragma once

#include <memory>

class b2World;

class Scene
{
public:
	Scene();
	~Scene();

private:
	std::unique_ptr<b2World> m_world;
	const float m_kGravity;
};

