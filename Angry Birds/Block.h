#pragma once

#include "Object.h"

#include <Box2D\Box2D.h>

class Scene;
struct NVGcontext;

class Block : public Object
{
public:
	Block(Scene& scene, float posX, float posY, float width, float height);
	virtual ~Block() override;
	Block(const Block&) = delete;
	Block(Block&&) = delete;

	void startContact(Object*) override;
	void endContact(Object*) override;

	void draw(NVGcontext*) const override;

	void decreaseHealth();

private:
	float m_width;
	float m_height;
	float r, g, b;
	int m_health = 3;
};

