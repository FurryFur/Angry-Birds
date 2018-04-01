#pragma once

#include <Box2D\Box2D.h>

class Scene;
struct NVGcontext;

class Birb
{
public:
	Birb(Scene& scene, float posX, float posY);
	~Birb();
	Birb(const Birb&) = delete;
	Birb(Birb&&) = delete;

	void draw(NVGcontext*);
	const b2BodyDef& Birb::getBodyDef();

private:
	b2Body* m_body;
	b2BodyDef m_bodyDef;
};

