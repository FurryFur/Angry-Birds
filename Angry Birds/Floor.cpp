#include "Floor.h"

#include "Scene.h"

#include <nanovg.h>
#include <Box2D\Box2D.h>

Floor::Floor(Scene& scene, float posX, float posY)
{
	m_bodyDef.position.Set(posX, posY);
	m_body = scene.addObject(std::unique_ptr<Object>(this));

	b2PolygonShape groundBox;
	groundBox.SetAsBox(50.0f/ Scene::s_kPixelsPerMeter, 10.0f/ Scene::s_kPixelsPerMeter);

	m_body->CreateFixture(&groundBox, 0.0f);
}

Floor::~Floor()
{
}

const b2BodyDef& Floor::getBodyDef() const
{
	return m_bodyDef;
}

void Floor::draw(NVGcontext* vg) const
{
	nvgFillColor(vg, nvgRGBA(255, 192, 0, 128));
	nvgStrokeColor(vg, nvgRGBA(255, 192, 0, 255));

	nvgBeginPath(vg);
	nvgRect(
		vg,
		m_body->GetPosition().x * Scene::s_kPixelsPerMeter,
		m_body->GetPosition().y * Scene::s_kPixelsPerMeter,
		50,
		10
	);
	nvgFill(vg);
	nvgStroke(vg);
}
