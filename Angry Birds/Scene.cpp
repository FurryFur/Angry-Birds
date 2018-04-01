#include "Scene.h"

#include "Birb.h"
#include "ContactListener.h"

#include <Box2D\Box2D.h>

const float Scene::s_kPixelsPerMeter = 32.0f;
const float Scene::s_kGravity = 10;

Scene::Scene()
	: m_world{ std::make_unique<b2World>(b2Vec2(0.0f, s_kGravity)) }
{
	ContactListener* newContact = new ContactListener;
	m_world->SetAllowSleeping(true);
	m_world->SetContinuousPhysics(true);
	m_world->SetContactListener(newContact);
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

b2Body* Scene::addObject(std::unique_ptr<Object> obj)
{
	b2Body* body = m_world->CreateBody(&obj->getBodyDef());
	m_objs.push_back(std::move(obj));

	return body;
}

void Scene::removeObjects()
{
	if (m_killList.size() != 0)
	{
		for (auto& kill : m_killList)
		{
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

Birb* Scene::getCurrentBirb()
{
	for (auto& obj : m_objs) {
		Birb* birb = dynamic_cast<Birb*>(obj.get());
		if (birb)
			return birb;
	}

	return nullptr;
}
