#pragma once

#include "Object.h"
#include <Box2D\Box2D.h>

class Scene;
struct NVGcontext;

class Hinge : public Object
{
public:
	Hinge(Scene& scene, float posX, float posY, b2BodyType type);
	virtual ~Hinge() override;
	Hinge(const Hinge&) = delete;
	Hinge(Hinge&&) = delete;

	void startContact(Object*) override;
	void endContact(Object*) override;

	void draw(NVGcontext*) const override;

private:

};

