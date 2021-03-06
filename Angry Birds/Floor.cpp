#include "Floor.h"

#include "Scene.h"

#include <nanovg.h>
#include <Box2D\Box2D.h>

Floor::Floor(Scene& scene, float posX, float posY, float width, float height)
	:
	m_width(width),
	m_height(height),
	Object(scene)

{
	m_bodyDef.type = b2_kinematicBody;
	m_bodyDef.position.Set(posX, posY);
	m_body = scene.addObject(std::unique_ptr<Object>(this));

	b2PolygonShape groundBox;
	groundBox.SetAsBox(m_width/2, m_height/2);

	b2FixtureDef fixtureDef;
	//fixtureDef.friction = 1.0f;
	fixtureDef.density = 0.0f;
	fixtureDef.shape = &groundBox;

	m_body->CreateFixture(&fixtureDef);

	m_body->SetUserData(this);
}

Floor::~Floor()
{
}

void Floor::startContact(Object* other)
{
	// hit floor
}

void Floor::endContact(Object* other)
{
	// floor no hit
}

void Floor::draw(NVGcontext* vg) const
{
	float pixelWidth = m_width * Scene::s_kPixelsPerMeter;
	float pixelHeight = m_height * Scene::s_kPixelsPerMeter;

	nvgFillColor(vg, nvgRGBA(255, 192, 0, 128));
	nvgStrokeColor(vg, nvgRGBA(255, 192, 0, 255));

	nvgBeginPath(vg);
	nvgRect(
		vg,
		m_body->GetPosition().x * Scene::s_kPixelsPerMeter - pixelWidth/2,
		m_body->GetPosition().y * Scene::s_kPixelsPerMeter - pixelHeight/2,
		pixelWidth,
		pixelHeight
	);
	nvgFill(vg);
	nvgStroke(vg);
}
