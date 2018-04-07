#pragma once

#include "Object.h"

#include <Box2D\Box2D.h>

class Scene;
struct NVGcontext;

class Birb : public Object
{
public:
	Birb(Scene& scene, float posX, float posY, float radius);
	virtual ~Birb() override;
	Birb(const Birb&) = delete;
	Birb(Birb&&) = delete;

	void draw(NVGcontext*) const override;

	void startContact(Object*) override;
	void endContact(Object*) override;

private:
	
	float m_birbRadius;
	float r, g, b;
};

