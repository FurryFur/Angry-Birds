#pragma once

#include <memory>
#include <vector>

class b2World;
class b2Body;
class b2Joint;
struct b2Vec2;

class SceneManager;
class ContactListener;
class Object;
struct NVGcontext;
class Birb;
class Block;

class Scene
{
public:
	virtual ~Scene();
	Scene(const Scene&) = delete;
	Scene(Scene&&) = delete;

	// Construct a new scene based on the derived scene type.
	// Useful for restarting the level.
	virtual std::unique_ptr<Scene> createNew() const = 0;

	void update();
	void checkAndEndLevel();

	b2Body* addObject(std::unique_ptr<Object>);
	b2Joint* createRevoluteJoint(b2Body*, b2Body*, b2Vec2, b2Vec2, bool, float);
	b2Joint* createDistanceJoint(b2Body*, b2Body*, b2Vec2, b2Vec2, float);
	b2Joint* createPrismaticJoint(b2Body*, b2Body*, float, float);
	Block* createRopeStructure(Scene&, float, float, int, float, float);

	void removeObjects();
	void addToKillList(Object*);
	void draw(NVGcontext*);
	int getLevelNum() const;

	Birb* getNextFlingableBirb();

	static const float s_kPixelsPerMeter;
	static const float s_kGravity;

protected:
	Scene(SceneManager&);

	int m_levelNumber;
	SceneManager& m_manager;

	std::unique_ptr<ContactListener> m_contactListener;
	std::vector<std::unique_ptr<Object>> m_objs;
	std::unique_ptr<b2World> m_world;
	std::vector<Object*> m_killList;
	int m_pigCount = 0;

	std::vector<Birb*> m_birbs;
	int m_nextFlingableBirbIdx = 0;
};

