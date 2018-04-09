#include "Birb.h"

#include "Scene.h"

#include <nanovg.h>
#include <Box2D\Box2D.h>

Birb::Birb(Scene& scene, float posX, float posY, float radius)
	:
	Object(scene)
{
	m_birbRadius = radius;
	m_bodyDef.position.Set(posX, posY);
}

Birb::~Birb()
{
}

void Birb::draw(NVGcontext* vg) const
{
	nvgFillColor(vg, nvgRGBA(r, g, b, 128));
	nvgStrokeColor(vg, nvgRGBA(255, 192, 0, 255));

	nvgBeginPath(vg);
	nvgCircle(
		vg,
		m_body->GetPosition().x * Scene::s_kPixelsPerMeter,
		m_body->GetPosition().y * Scene::s_kPixelsPerMeter,
		m_birbRadius * Scene::s_kPixelsPerMeter
	);
	nvgFill(vg);
	nvgStroke(vg);
}
