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

	void startContact() override;
	void endContact() override;

	void draw(NVGcontext*) const override;
	const b2BodyDef& Floor::getBodyDef() const override;

private:
	b2Body * m_body;
	b2BodyDef m_bodyDef;
	float m_height;
	float m_width;
};