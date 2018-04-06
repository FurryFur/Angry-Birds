#include "Block.h"
#include "Birb.h"

#include "Scene.h"

#include <nanovg.h>
#include <Box2D\Box2D.h>

Block::Block(Scene& scene, float posX, float posY, float width, float height)
	:
	m_width(width),
	m_height(height),
	Object(scene)

{
	m_bodyDef.type = b2_dynamicBody;
	m_bodyDef.position.Set(posX, posY);
	m_body = scene.addObject(std::unique_ptr<Object>(this));

	b2PolygonShape dynamicBox;
	dynamicBox.SetAsBox(m_width/2, m_height/2);

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicBox;
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
	//delete this;
	/*if(dynamic_cast<Birb*>(other) != nullptr)
		m_gameScene.addToKillList(this);*/
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

	nvgFillColor(vg, nvgRGBA(255, 192, 0, 128));
	nvgStrokeColor(vg, nvgRGBA(255, 192, 0, 255));

	nvgBeginPath(vg);
	nvgRect(
		vg,
		-pixelWidth / 2,
		-pixelHeight / 2,
		pixelWidth,
		pixelHeight
	);
	nvgFill(vg);
	nvgStroke(vg);

	nvgRestore(vg);
}