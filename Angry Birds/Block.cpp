#include "Block.h"
#include "Birb.h"
#include "Particle.h"

#include "Scene.h"

#include <nanovg.h>
#include <Box2D\Box2D.h>

Block::Block(Scene& scene, float posX, float posY, float width, float height, Shape shape, Type type)
	:
	m_width(width),
	m_height(height),
	m_shape(shape),
	m_type(type),
	Object(scene)

{
	if (type == METAL) {
		m_color = { 125,125,125 };
	} 
	else if (type == WOOD) {
		m_color = { 12.0f * m_health, 10.0f * m_health, 8.0f * m_health };
	}

	m_bodyDef.type = b2_dynamicBody;
	m_bodyDef.position.Set(posX, posY);
	m_bodyDef.angularDamping = 0.9f;

	m_body = scene.addObject(std::unique_ptr<Object>(this));

	b2FixtureDef fixtureDef;
	b2CircleShape dynamicCircle;
	b2PolygonShape dynamicBox;

	if (shape == RECTANGLE)
	{
		dynamicBox.SetAsBox(m_width / 2, m_height / 2);
		fixtureDef.shape = &dynamicBox;
	}
	else
	{
		dynamicCircle.m_radius = width;
		fixtureDef.shape = &dynamicCircle;
	}

	fixtureDef.density = 1.0f;
	fixtureDef.friction = 0.3f;
	fixtureDef.restitution = 0.5f;

	m_body->CreateFixture(&fixtureDef);

	m_body->SetUserData(this);
}

Block::~Block()
{
}

void Block::startContact(Object* other)
{
	
	
}

void Block::preSolve(b2Contact* contact, Object* other, b2Vec2 velocity)
{
	float magnitude = velocity.Length();
	if (m_type == WOOD)
	{
		Particle* checkParticle = dynamic_cast<Particle*>(other);
		if (!m_dead && ((magnitude > 15.0f && dynamic_cast<Block*>(other) != nullptr) ||
			(magnitude > 5.0f && dynamic_cast<Birb*>(other) != nullptr) ||
			(checkParticle != nullptr && !checkParticle->isShrapnel())))
		{
			magnitude > 10.0f ? m_health -= 8 : m_health -= 1;

			decreaseHealth();

			if (m_health <= 0)
			{
				contact->SetEnabled(false);
				m_gameScene.addToKillList(this);
				m_dead = true;
			}
		}
	}
}

void Block::endContact(Object* other)
{
}

void Block::draw(NVGcontext* vg) const
{
	float pixelWidth = m_width * Scene::s_kPixelsPerMeter;
	float pixelHeight = m_height * Scene::s_kPixelsPerMeter;

	b2Vec2 pixelPosition = b2Vec2(m_body->GetPosition().x * Scene::s_kPixelsPerMeter, m_body->GetPosition().y * Scene::s_kPixelsPerMeter);

	nvgSave(vg);

	nvgTranslate(vg, pixelPosition.x, pixelPosition.y);
	nvgRotate(vg, (m_body->GetAngle()));

	nvgFillColor(vg, nvgRGBA(m_color.x, m_color.y, m_color.z, 128));
	nvgStrokeColor(vg, nvgRGBA(255, 255, 255, 255));

	nvgBeginPath(vg);
	if (m_shape == RECTANGLE)
	{
		nvgRect(
			vg,
			-pixelWidth / 2,
			-pixelHeight / 2,
			pixelWidth,
			pixelHeight
		);
	}
	else
	{
		nvgCircle(
			vg,
			0,
			0,
		     pixelWidth
		);
	}
	
	nvgFill(vg);
	nvgStroke(vg);

	nvgRestore(vg);
}

void Block::decreaseHealth()
{
	m_color = { 12.0f * m_health, 10.0f * m_health, 8.0f * m_health };
}
