#include "Object.h"
#include "Scene.h"

Object::Object(Scene& scene)
	:
	m_gameScene(scene)
{
}

const b2BodyDef& Object::getBodyDef() const
{
	return m_bodyDef;
}

b2Body& Object::getBody()
{
	return *m_body;
}

void Object::postSolve(Object*, const b2ContactImpulse*)
{

}

void Object::preSolve(b2Contact *, Object *, b2Vec2)
{
}

