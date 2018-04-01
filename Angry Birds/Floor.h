#pragma once

#include "Object.h"

#include <Box2D\Box2D.h>

class Scene;
struct NVGcontext;

class Floor : public Object
{
public:
	Floor(Scene& scene, float posX, float posY);
	virtual ~Floor() override;
	Floor(const Floor&) = delete;
	Floor(Floor&&) = delete;

	void draw(NVGcontext*) const override;
	const b2BodyDef& Floor::getBodyDef() const override;

private:
	b2Body * m_body;
	b2BodyDef m_bodyDef;
};