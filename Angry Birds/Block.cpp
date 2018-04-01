#include "Block.h"

#include "Scene.h"

#include <nanovg.h>
#include <Box2D\Box2D.h>

Block::Block(Scene& scene, float posX, float posY, float width, float height)
	:
	m_width(width),
	m_height(height)
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
}

Block::~Block()
{
}

void Block::startContact()
{
	//delete this;
}

void Block::endContact()
{

}

void Block::draw(NVGcontext* vg) const
{
	float pixelWidth = m_width * Scene::s_kPixelsPerMeter;
	float pixelHeight = m_height * Scene::s_kPixelsPerMeter;

	nvgFillColor(vg, nvgRGBA(255, 192, 0, 128));
	nvgStrokeColor(vg, nvgRGBA(255, 192, 0, 255));

	nvgBeginPath(vg);
	nvgRect(
		vg,
		m_body->GetPosition().x * Scene::s_kPixelsPerMeter - pixelWidth / 2,
		m_body->GetPosition().y * Scene::s_kPixelsPerMeter - pixelHeight / 2,
		pixelWidth,
		pixelHeight
	);
	nvgFill(vg);
	nvgStroke(vg);
}