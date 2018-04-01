#include "Object.h"

const b2BodyDef& Object::getBodyDef() const
{
	return m_bodyDef;
}

b2Body& Object::getBody()
{
	return *m_body;
}
