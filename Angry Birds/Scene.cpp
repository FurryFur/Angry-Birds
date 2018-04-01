#include "Scene.h"

#include "Birb.h"

#include <Box2D\Box2D.h>

const float Scene::s_kPixelsPerMeter = 32.0f;
const float Scene::s_kGravity = 10;

Scene::Scene()
	: m_world{ std::make_unique<b2World>(b2Vec2(0.0f, s_kGravity)) }
{
	m_world->SetAllowSleeping(true);
	m_world->SetContinuousPhysics(true);
	//m_world->SetContactListener(this);
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
}

b2Body* Scene::addObject(std::unique_ptr<Object> obj)
{
	b2Body* body = m_world->CreateBody(&obj->getBodyDef());
	m_objs.push_back(std::move(obj));

	return body;
}

void Scene::draw(NVGcontext* vg)
{
	for (auto& obj : m_objs) {
		obj->draw(vg);
	}
}
