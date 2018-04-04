#pragma once

#include "Object.h"

#include <Box2D\Box2D.h>

class Scene;
struct NVGcontext;

class Floor : public Object
{
public:
	Floor(Scene& scene, float posX, float posY, float width, float height);
	virtual ~Floor() override;
	Floor(const Floor&) = delete;
	Floor(Floor&&) = delete;

	void startContact(Object*) override;
	void endContact(Object*) override;

	void draw(NVGcontext*) const override;

private:
	float m_height;
	float m_width;
};