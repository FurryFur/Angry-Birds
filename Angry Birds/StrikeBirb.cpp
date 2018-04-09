#include "StrikeBirb.h"

#include "Scene.h"
#include "Particle.h"
#include "Pig.h"

#include <nanovg.h>
#include <glm\glm.hpp>

StrikeBirb::StrikeBirb(Scene& scene, float posX, float posY, float radius)
	: Birb(scene, posX, posY, radius)
	, inFlight{ false }
{
	Initialize(scene);
}


StrikeBirb::~StrikeBirb()
{
}

void StrikeBirb::Initialize(Scene& scene)
{
	// Bird color
	r = 255;
	g = 255;
	b = 0;

	m_bodyDef.type = b2_dynamicBody;
	m_bodyDef.angularDamping = 0.9f;
	m_bodyDef.linearDamping = 0.25f;

	m_body = scene.addObject(std::unique_ptr<Object>(this));

	b2CircleShape dynamicBox;
	dynamicBox.m_radius = m_birbRadius;

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicBox;
	fixtureDef.density = 3;
	fixtureDef.friction = 1.0f;
	fixtureDef.restitution = 0.5f;

	m_body->CreateFixture(&fixtureDef);
	m_body->SetUserData(this);
}

void StrikeBirb::draw(NVGcontext* vg) const
{
	Birb::draw(vg);
	
	if (inFlight) {
		m_body->SetTransform(m_body->GetPosition(), glm::atan(m_body->GetLinearVelocity().y, m_body->GetLinearVelocity().x));
	}

	b2Vec2 pixelPosition = b2Vec2(m_body->GetPosition().x * Scene::s_kPixelsPerMeter, m_body->GetPosition().y * Scene::s_kPixelsPerMeter);
	float pixelRadius = m_birbRadius * Scene::s_kPixelsPerMeter;

	nvgSave(vg);

	nvgTranslate(vg, pixelPosition.x, pixelPosition.y);
	nvgRotate(vg, m_body->GetAngle());
	
	nvgStrokeColor(vg, nvgRGBA(255, 0, 0, 255));
	
	nvgBeginPath(vg);
	nvgMoveTo(vg, 0, 0);
	nvgLineTo(vg, pixelRadius, 0);
	nvgStroke(vg);

	nvgRestore(vg);
}

void StrikeBirb::startContact(Object* other)
{
	if (!dynamic_cast<Particle*>(other) && !dynamic_cast<Pig*>(other))
	{
		inFlight = false;
	}
}