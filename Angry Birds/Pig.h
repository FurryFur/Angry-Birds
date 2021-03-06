#pragma once

#include "Object.h"

#include <Box2D\Box2D.h>

class Scene;
struct NVGcontext;

class Pig : public Object
{
public:
	Pig(Scene& scene, float posX, float posY, float radius);
	virtual ~Pig() override;
	Pig(const Pig&) = delete;
	Pig(Pig&&) = delete;

	void draw(NVGcontext*) const override;

	void startContact(Object*) override;
	void endContact(Object*) override;
	void preSolve(b2Contact*, Object*, b2Vec2) override;

private:
	float m_PigRadius;
	unsigned char r, g, b;
	bool m_dead;
};

