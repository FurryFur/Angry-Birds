#pragma once

#include <Box2D\Box2D.h>

class Scene;
struct NVGcontext;

class Object
{
public:
	Object(Scene&);
	virtual ~Object() {};

	virtual void draw(NVGcontext*) const = 0;
	const b2BodyDef& getBodyDef() const;
	b2Body& getBody();

	virtual void startContact(Object*);
	virtual void endContact(Object*);

	virtual void preSolve(b2Contact*, Object*, b2Vec2);


protected:
	b2Body * m_body;
	b2BodyDef m_bodyDef;
	Scene& m_gameScene;
};



