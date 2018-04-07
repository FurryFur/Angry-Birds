#include "Scene.h"
#include "SceneManager.h"

#include "Birb.h"
#include "Pig.h"

#include "ContactListener.h"

#include <Box2D\Box2D.h>
#include <sstream>

const float Scene::s_kPixelsPerMeter = 32.0f;
const float Scene::s_kGravity = 10;

Scene::Scene(SceneManager& _manager)
	: m_world{ std::make_unique<b2World>(b2Vec2(0.0f, s_kGravity)) }
	, m_manager(_manager)
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

	checkAndEndLevel();
}

void Scene::checkAndEndLevel()
{
	if (m_pigCount <= 0) {
		std::stringstream ss;
		ss << "Level " << (m_levelNumber+1);
		m_manager.loadNewScene(ss.str());
	}
	else if (m_nextFlingableBirbIdx >= m_birbs.size()) {
		// If we have fired all birbs then check if all birbs are stationary
		bool allSleeping = true;
		for (Birb* birb : m_birbs) {
			if (!birb->getBody().IsActive()) {
				allSleeping = false;
				break;
			}

			if (birb->getBody().IsAwake() && birb->getBody().GetLinearVelocity().Length() > 1.0f) {
				allSleeping = false;
				break;
			}
		}

		// When all birbs are stationary restart the level
		if (allSleeping) {
			m_manager.restartLevel();
		}
	}
}

b2Body* Scene::addObject(std::unique_ptr<Object> obj)
{
	// Add to birb list if birb
	Birb* birb = dynamic_cast<Birb*>(obj.get());
	if (birb) {
		m_birbs.push_back(birb);
	}

	// Create physics body and add to physics simulation
	b2Body* body = m_world->CreateBody(&obj->getBodyDef());

	// Store unique pointer to object
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
			{
				m_pigCount--;
			}

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

int Scene::getLevelNum() const
{
	return m_levelNumber;
}

Birb* Scene::getNextFlingableBirb()
{
	// Get the next flingable birb in the scene
	Birb* nextBirb = nullptr;
	if (m_nextFlingableBirbIdx < m_birbs.size()) {
		nextBirb = m_birbs[m_nextFlingableBirbIdx];
		++m_nextFlingableBirbIdx;
	}

	return nextBirb;
}