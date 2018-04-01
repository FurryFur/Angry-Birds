#include "Birb.h"

#include "Scene.h"

#include <nanovg.h>
#include <Box2D\Box2D.h>

Birb::Birb(Scene& scene, float posX, float posY)
{
	m_bodyDef.type = b2_dynamicBody;
	m_bodyDef.position.Set(posX, posY);
	m_body = scene.addObject(std::unique_ptr<Object>(this));

	b2CircleShape dynamicBox;
	dynamicBox.m_radius = 1.0f / Scene::s_kPixelsPerMeter;

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicBox;
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 0.3f;
	fixtureDef.restitution = 0.5f;

	m_body->CreateFixture(&fixtureDef);
}

Birb::~Birb()
{
}

const b2BodyDef& Birb::getBodyDef() const
{
	return m_bodyDef;
}

void Birb::draw(NVGcontext* vg) const
{
	nvgFillColor(vg, nvgRGBA(255, 192, 0, 128));
	nvgStrokeColor(vg, nvgRGBA(255, 192, 0, 255));

	nvgBeginPath(vg);
	nvgCircle(
		vg,
		m_body->GetPosition().x * Scene::s_kPixelsPerMeter,
		m_body->GetPosition().y * Scene::s_kPixelsPerMeter,
		10
	);
	nvgFill(vg);
	nvgStroke(vg);
}
