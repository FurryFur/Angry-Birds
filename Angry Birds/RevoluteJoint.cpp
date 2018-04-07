#include "RevoluteJoint.h"

#include "Scene.h"

#include <nanovg.h>
#include <Box2D\Box2D.h>

Hinge::Hinge(Scene& scene, float posX, float posY, b2BodyType type)
	:
	Object(scene)

{
	m_bodyDef.position.Set(posX, posY);
	m_bodyDef.type = type;

	b2FixtureDef fixtureDef;
	fixtureDef.density = 1;

	b2CircleShape circleShape;
	circleShape.m_radius = 0.1f;

	fixtureDef.shape = &circleShape;

	m_body = scene.addObject(std::unique_ptr<Object>(this));
}

Hinge::~Hinge()
{
}

void Hinge::startContact(Object* other)
{
	// hit floor
}

void Hinge::endContact(Object* other)
{
	// floor no hit
}

void Hinge::draw(NVGcontext* vg) const
{
	nvgFillColor(vg, nvgRGBA(255, 192, 0, 128));
	nvgStrokeColor(vg, nvgRGBA(255, 192, 0, 255));

	nvgBeginPath(vg);
	nvgCircle(
		vg,
		m_body->GetPosition().x * Scene::s_kPixelsPerMeter,
		m_body->GetPosition().y * Scene::s_kPixelsPerMeter,
		0.1f * Scene::s_kPixelsPerMeter
	);
	nvgFill(vg);
	nvgStroke(vg);
}
