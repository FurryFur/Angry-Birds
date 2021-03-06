#include "Pig.h"
#include "Birb.h"
#include "Block.h"
#include "Particle.h"

#include "Scene.h"

#include "Floor.h"

#include <nanovg.h>
#include <Box2D\Box2D.h>

Pig::Pig(Scene& scene, float posX, float posY, float radius)
	:
	Object(scene)
{
	// Pig color
	r = 0;
	g = 255;
	b = 0;

	m_PigRadius = radius;

	m_bodyDef.type = b2_dynamicBody;
	m_bodyDef.angularDamping = 0.75;
	m_bodyDef.position.Set(posX, posY);
	m_body = scene.addObject(std::unique_ptr<Object>(this));

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

}

void Pig::endContact(Object* other)
{

}

void Pig::preSolve(b2Contact* contact, Object* other, b2Vec2 velocity)
{
	float magnitude = velocity.Length();
	Particle* checkParticle = dynamic_cast<Particle*>(other);

	if ((magnitude > 20.0f && dynamic_cast<Block*>(other) != nullptr) ||
		(magnitude > 5.0f && dynamic_cast<Birb*>(other) != nullptr) ||
		(checkParticle != nullptr && !checkParticle->isShrapnel()))
	{
		if (!m_dead)
		{
			contact->SetEnabled(false);
			m_gameScene.addToKillList(this);
			m_dead = true;
		}

	}
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
