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

	virtual void Initialize(Scene& scene) = 0;
	void draw(NVGcontext*) const override;

	void startContact(Object*) override;
	void endContact(Object*) override;

protected:
	float m_birbRadius;
	float r, g, b;

private:
	
};

