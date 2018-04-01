#pragma once

#include <memory>
#include <vector>

class b2World;
class b2Body;
class Birb;
struct NVGcontext;

class Scene
{
public:
	Scene();
	~Scene();

	void update();
	b2Body* addObject(std::unique_ptr<Birb>);
	void draw(NVGcontext*);

	static const float s_kPixelsPerMeter;
	static const float s_kGravity;

private:
	std::vector<std::unique_ptr<Birb>> m_birbs;
	std::unique_ptr<b2World> m_world;
};

