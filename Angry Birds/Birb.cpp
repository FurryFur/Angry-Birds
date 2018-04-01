#include "Birb.h"

#include "Scene.h"

#include <nanovg.h>
#include <Box2D\Box2D.h>

Birb::Birb(Scene& scene, float posX, float posY)
{
	m_bodyDef.type = b2_dynamicBody;
	m_bodyDef.position.Set(posX, posY);
	m_body = scene.addObject(std::unique_ptr<Birb>(this));

	b2PolygonShape dynamicBox;
	dynamicBox.SetAsBox(1.0f, 1.0f);

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicBox;
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 0.3f;

	m_body->CreateFixture(&fixtureDef);
}

Birb::~Birb()
{
}

const b2BodyDef& Birb::getBodyDef()
{
	return m_bodyDef;
}

void Birb::draw(NVGcontext* vg)
{
	nvgFillColor(vg, nvgRGBA(255, 192, 0, 128));
	nvgStrokeColor(vg, nvgRGBA(255, 192, 0, 255));

	nvgBeginPath(vg);
	nvgCircle(vg, m_body->GetPosition().x, m_body->GetPosition().y, 10);
	nvgFill(vg);
	nvgStroke(vg);
}