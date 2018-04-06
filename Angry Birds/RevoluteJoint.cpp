#include "RevoluteJoint.h"

#include "Scene.h"

#include <nanovg.h>
#include <Box2D\Box2D.h>

RevoluteJoint::RevoluteJoint(Scene& scene, float posX, float posY, b2Body* connection, b2BodyType type)
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
	scene.createJoint(m_body, connection);
}

RevoluteJoint::~RevoluteJoint()
{
}

void RevoluteJoint::startContact(Object* other)
{
	// hit floor
}

void RevoluteJoint::endContact(Object* other)
{
	// floor no hit
}

void RevoluteJoint::draw(NVGcontext* vg) const
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
