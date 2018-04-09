#pragma once

#include "Object.h"
#include "Utils.h"

#include <Box2D\Box2D.h>

enum Type
{
	WOOD,
	METAL
};

enum Shape
{
	CIRCLE,
	RECTANGLE
};

class Scene;
struct NVGcontext;

class Block : public Object
{
public:
	Block(Scene& scene, float posX, float posY, float width, float height, Shape shape, Type type);
	virtual ~Block() override;
	Block(const Block&) = delete;
	Block(Block&&) = delete;

	void startContact(Object*) override;
	void endContact(Object*) override;
	void preSolve(b2Contact*, Object*, b2Vec2) override;

	void draw(NVGcontext*) const override;

	void decreaseHealth();

private:
	Shape m_shape;
	Type m_type;
	float m_width;
	float m_height;
	Color m_color;
	int m_health = 15;
	bool m_dead = false;
};

