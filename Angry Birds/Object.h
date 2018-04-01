#pragma once

#include <Box2D\Box2D.h>

struct NVGcontext;

class Object
{
public:
	virtual ~Object() {};

	virtual void draw(NVGcontext*) const = 0;
	const b2BodyDef& getBodyDef() const;
	b2Body& getBody();

	virtual void startContact() = 0;
	virtual void endContact() = 0;

protected:
	b2Body * m_body;
	b2BodyDef m_bodyDef;
};



