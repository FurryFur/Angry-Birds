#include "Particle.h"
#include "Birb.h"
#include "Block.h"

#include "Scene.h"

#include "Floor.h"

#include <nanovg.h>
#include <Box2D\Box2D.h>

Particle::Particle(Scene& scene, float posX, float posY, float blastPower, b2Vec2 rayDir, int rays)
	:
	Object(scene)
{
	// Particle color
	r = 255;
	g = 0;
	b = 0;

	m_bodyDef.type = b2_dynamicBody;
	m_bodyDef.fixedRotation = true; // rotation not necessary
	m_bodyDef.bullet = true; // prevent tunneling at high speed
	m_bodyDef.linearDamping = 10; // drag due to moving through air
	m_bodyDef.gravityScale = 0; // ignore gravity
	m_bodyDef.position.Set(posX, posY);
	m_originalPos.Set(posX, posY);
	m_bodyDef.linearVelocity = blastPower * rayDir;

	m_body = scene.addObject(std::unique_ptr<Object>(this));

	m_ParticleRadius = 0.05f;

	b2CircleShape circleShape;
	circleShape.m_radius = m_ParticleRadius; // very small

	b2FixtureDef fd;
	fd.shape = &circleShape;
	fd.density = 60 / (float)rays; // very high - shared across all particles
	fd.friction = 0; // friction not necessary
	fd.restitution = 0.99f; // high restitution to reflect off obstacles
	m_body->CreateFixture(&fd);

	m_body->SetSleepingAllowed(true);
	m_body->SetUserData(this);

}

Particle::~Particle()
{
}

void Particle::startContact(Object* other)
{
}

void Particle::endContact(Object *)
{
}

void Particle::preSolve(b2Contact* contact, Object* other, b2Vec2 velocity)
{
	if (!m_dead && dynamic_cast<Particle*>(other) == nullptr &&
		 dynamic_cast<Birb*>(other) == nullptr)
	{
		contact->SetEnabled(false);
		m_gameScene.addToKillList(this);
		m_dead = true;
	}
}

void Particle::draw(NVGcontext* vg) const
{
	nvgFillColor(vg, nvgRGBA(r, g, b, 50));
	nvgStrokeColor(vg, nvgRGBA(255, 0, 0, 50));

	nvgBeginPath(vg);

	nvgMoveTo(vg, meterToPixel(m_originalPos.x), meterToPixel(m_originalPos.y));
	nvgLineTo(vg, meterToPixel(m_body->GetPosition().x), meterToPixel(m_body->GetPosition().y));

	nvgCircle(
		vg,
		m_body->GetPosition().x * Scene::s_kPixelsPerMeter,
		m_body->GetPosition().y * Scene::s_kPixelsPerMeter,
		m_ParticleRadius * Scene::s_kPixelsPerMeter
	);
	nvgFill(vg);
	nvgStroke(vg);
}
