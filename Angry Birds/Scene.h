#pragma once

#include <memory>
#include <vector>

class b2World;
class b2Body;
class b2Joint;

class Object;
struct NVGcontext;
class Birb;

class Scene
{
public:
	virtual ~Scene();
	Scene(const Scene&) = delete;
	Scene(Scene&&) = delete;

	void update();
	void checkAndEndLevel();

	b2Body* addObject(std::unique_ptr<Object>);
	b2Joint* createJoint(b2Body*, b2Body*);
	void removeObjects();
	void addToKillList(Object*);
	void draw(NVGcontext*);

	Birb* getCurrentBirb();

	static const float s_kPixelsPerMeter;
	static const float s_kGravity;

protected:
	Scene();

	std::vector<std::unique_ptr<Object>> m_objs;
	std::unique_ptr<b2World> m_world;
	std::vector<Object*> m_killList;
	int m_pigCount = 0;
};

