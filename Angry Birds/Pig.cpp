#include "Pig.h"
#include "Birb.h"

#include "Scene.h"

#include <nanovg.h>
#include <Box2D\Box2D.h>

Pig::Pig(Scene& scene, float posX, float posY)
	:
	Object(scene)
{
	// Pig color
	r = 0;
	g = 255;
	b = 0;

	m_bodyDef.type = b2_dynamicBody;
	m_bodyDef.position.Set(posX, posY);
	m_body = scene.addObject(std::unique_ptr<Object>(this));

	m_PigRadius = 1.0f;

	b2CircleShape dynamicBox;
	dynamicBox.m_radius = m_PigRadius;

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicBox;
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 0.3f;
	fixtureDef.restitution = 0.5f;

	m_body->CreateFixture(&fixtureDef);

	m_body->SetUserData(this);
}

Pig::~Pig()
{
}

void Pig::startContact(Object* other)
{
	if (dynamic_cast<Birb*>(other) != nullptr)
		m_gameScene.addToKillList(this);
}

void Pig::endContact(Object* other)
{

}

void Pig::draw(NVGcontext* vg) const
{
	nvgFillColor(vg, nvgRGBA(r, g, b, 128));
	nvgStrokeColor(vg, nvgRGBA(255, 192, 0, 255));

	nvgBeginPath(vg);
	nvgCircle(
		vg,
		m_body->GetPosition().x * Scene::s_kPixelsPerMeter,
		m_body->GetPosition().y * Scene::s_kPixelsPerMeter,
		m_PigRadius * Scene::s_kPixelsPerMeter
	);
	nvgFill(vg);
	nvgStroke(vg);
}
