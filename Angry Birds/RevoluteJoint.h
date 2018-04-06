#pragma once

#include "Object.h"
#include <Box2D\Box2D.h>

class Scene;
struct NVGcontext;

class RevoluteJoint : public Object
{
public:
	RevoluteJoint(Scene& scene, float posX, float posY, b2Body* connection, b2BodyType type);
	virtual ~RevoluteJoint() override;
	RevoluteJoint(const RevoluteJoint&) = delete;
	RevoluteJoint(RevoluteJoint&&) = delete;

	void startContact(Object*) override;
	void endContact(Object*) override;

	void draw(NVGcontext*) const override;

private:

};

