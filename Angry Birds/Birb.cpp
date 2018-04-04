#include "Birb.h"

#include "Scene.h"

#include <nanovg.h>
#include <Box2D\Box2D.h>

Birb::Birb(Scene& scene, float posX, float posY)
	:
	Object(scene)
{
	// Bird color
	r = 0;
	g = 255;
	b = 0;

	m_bodyDef.type = b2_dynamicBody;
	m_bodyDef.position.Set(posX, posY);
	m_body = scene.addObject(std::unique_ptr<Object>(this));

	m_birbRadius = 1.0f;

	b2CircleShape dynamicBox;
	dynamicBox.m_radius = m_birbRadius;

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicBox;
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 0.3f;
	fixtureDef.restitution = 0.5f;

	m_body->CreateFixture(&fixtureDef);

	m_body->SetUserData(this);
}

Birb::~Birb()
{
}

void Birb::startContact(Object* other)
{
	r = 255;
	g = 0;
	b = 0;
}

void Birb::endContact(Object* other)
{
	r = 0;
	g = 255;
	b = 0;
}

void Birb::draw(NVGcontext* vg) const
{
	nvgFillColor(vg, nvgRGBA(r, g, b, 128));
	nvgStrokeColor(vg, nvgRGBA(255, 192, 0, 255));

	nvgBeginPath(vg);
	nvgCircle(
		vg,
		m_body->GetPosition().x * Scene::s_kPixelsPerMeter,
		m_body->GetPosition().y * Scene::s_kPixelsPerMeter,
		m_birbRadius * Scene::s_kPixelsPerMeter
	);
	nvgFill(vg);
	nvgStroke(vg);
}
