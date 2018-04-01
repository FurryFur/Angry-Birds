#include "Scene.h"

#include "Birb.h"

#include <Box2D\Box2D.h>

Scene::Scene()
	: m_kGravity{ 9.81f }
	, m_world{ std::make_unique<b2World>(b2Vec2(0.0f, m_kGravity)) }
{
	//m_world->SetAllowSleeping(true);
	//m_world->SetContinuousPhysics(true);
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

b2Body* Scene::addObject(std::unique_ptr<Birb> birb)
{
	b2Body* body = m_world->CreateBody(&birb->getBodyDef());
	m_birbs.push_back(std::move(birb));

	return body;
}

void Scene::draw(NVGcontext* vg)
{
	for (auto& birb : m_birbs) {
		birb->draw(vg);
	}
}
