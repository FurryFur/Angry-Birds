#include "Scene.h"

#include "Birb.h"
#include "Pig.h"

#include "ContactListener.h"

#include <Box2D\Box2D.h>

const float Scene::s_kPixelsPerMeter = 32.0f;
const float Scene::s_kGravity = 10;

Scene::Scene()
	: m_world{ std::make_unique<b2World>(b2Vec2(0.0f, s_kGravity)) }
{
	m_contactListener = std::make_unique<ContactListener>();
	m_world->SetAllowSleeping(true);
	m_world->SetContinuousPhysics(true);
	m_world->SetContactListener(m_contactListener.get());
}


Scene::~Scene()
{

}

void Scene::update()
{
	static const float32 timeStep = 1.0f / 60.0f;
	static const int32 velocityIterations = 6;
	static const int32 positionIterations = 2;

	m_world->Step(timeStep, velocityIterations, positionIterations);

	removeObjects();
}

void Scene::checkAndEndLevel()
{
	if (m_pigCount <= 0)
	{

	}
}

b2Body* Scene::addObject(std::unique_ptr<Object> obj)
{
	b2Body* body = m_world->CreateBody(&obj->getBodyDef());
	m_objs.push_back(std::move(obj));

	return body;
}

b2Joint* Scene::createJoint(b2Body* m_bodyA, b2Body* m_bodyB)
{
	b2RevoluteJointDef revoluteJointDef;
	revoluteJointDef.bodyA = m_bodyA;
	revoluteJointDef.bodyB = m_bodyB;
	revoluteJointDef.collideConnected = false;
	revoluteJointDef.maxMotorTorque = 0.01f;
	revoluteJointDef.localAnchorA.Set(0, 0);//the top right corner of the box
	revoluteJointDef.localAnchorB.Set(0, 0);//center of the circle

	return m_world->CreateJoint(&revoluteJointDef);;
}

void Scene::removeObjects()
{
	if (m_killList.size() != 0)
	{
		for (auto& kill : m_killList)
		{
			if (dynamic_cast<Pig*>(kill) != nullptr)
				m_pigCount--; 

			m_world->DestroyBody(&kill->getBody());
			m_objs.erase(std::remove_if(m_objs.begin(), m_objs.end(), 
				[kill](std::unique_ptr<Object> &obj) {return obj.get() == kill; }),
				m_objs.end());
		}

		m_killList.clear();
	}
}

void Scene::addToKillList(Object* toKill)
{
	m_killList.push_back(toKill);
}

void Scene::draw(NVGcontext* vg)
{
	for (auto& obj : m_objs) {

		if(obj)
			obj->draw(vg);
	}
}

Birb* Scene::getNextFlingableBirb()
{
	static bool s_initialized = false;
	static std::vector<Birb*> s_birbs;
	static int s_nextBirbIdx = 0;

	// Construct birb list the first time this function is called
	if (!s_initialized) {
		for (auto& obj : m_objs) {
			Birb* birb = dynamic_cast<Birb*>(obj.get());
			if (birb)
				s_birbs.push_back(birb);
		}
		s_initialized = true;
	}

	// Get the next flingable birb in the scene
	Birb* nextBirb = nullptr;
	if (s_nextBirbIdx < s_birbs.size()) {
		nextBirb = s_birbs[s_nextBirbIdx];
		++s_nextBirbIdx;
	}

	return nextBirb;
}