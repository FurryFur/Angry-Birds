#pragma once

#include "Object.h"

#include <Box2D\Box2D.h>

class Scene;
struct NVGcontext;

class Birb : public Object
{
public:
	Birb(Scene& scene, float posX, float posY);
	virtual ~Birb() override;
	Birb(const Birb&) = delete;
	Birb(Birb&&) = delete;

	void draw(NVGcontext*) const override;
	const b2BodyDef& Birb::getBodyDef() const override;

	void startContact() override;
	void endContact() override;

private:
	b2Body* m_body;
	b2BodyDef m_bodyDef;
	float m_birbRadius;
	float r, g, b;
};

