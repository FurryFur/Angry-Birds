#include "Bomber.h"
#include "Scene.h"
#include "Pig.h"
#include "Block.h"


Bomber::Bomber(Scene& scene, float posX, float posY, float radius)
	: Birb(scene, posX, posY, radius)
{
	Initialize(scene);
}


Bomber::~Bomber()
{
}

void Bomber::Initialize(Scene& scene)
{
	// Bird color
	r = 0;
	g = 0;
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

void Bomber::startContact(Object* other)
{
	if (!m_dead && (dynamic_cast<Block*>(other) != nullptr || dynamic_cast<Pig*>(other) != nullptr))
	{
		m_gameScene.addToKillList(this);
		m_dead = true;

	}
}

void Bomber::endContact(Object* other)
{
	r = 0;
	g = 0;
	b = 0;
	
}
