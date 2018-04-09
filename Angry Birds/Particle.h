#pragma once

#include "Object.h"

#include <Box2D\Box2D.h>

class Scene;
struct NVGcontext;

class Particle : public Object
{
public:
	Particle(Scene& scene, float posX, float posY, float blastPower, b2Vec2 rayDir, int rays);
	virtual ~Particle() override;
	Particle(const Particle&) = delete;
	Particle(Particle&&) = delete;

	void startContact(Object*) override;
	void endContact(Object*) override;
	void preSolve(b2Contact*, Object*, b2Vec2) override;


	void draw(NVGcontext*) const override;

private:
	float m_ParticleRadius;
	float r, g, b;
	b2Vec2 m_originalPos;
	bool m_dead = false;
};

