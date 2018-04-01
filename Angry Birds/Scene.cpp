#include "Scene.h"

#include <Box2D\Box2D.h>

Scene::Scene()
	: m_kGravity{ 9.81f }
	, m_world{ std::make_unique<b2World>(b2Vec2(0.0f, m_kGravity)) }
{
	m_world->SetAllowSleeping(true);
	m_world->SetContinuousPhysics(true);
	//m_world->SetContactListener(this);
}


Scene::~Scene()
{

}
