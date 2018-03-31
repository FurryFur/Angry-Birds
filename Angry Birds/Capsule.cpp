#include "Capsule.h"

#include "Line.h"

#include <glm\glm.hpp>
#include <nanovg.h>

using namespace glm;

Capsule::Capsule(const glm::vec3& startPt, const glm::vec3& endPt, float radius)
	: m_startPt{ startPt }
	, m_endPt{ endPt }
	, m_radius{ radius }
{
}

Capsule::~Capsule()
{
}

void Capsule::draw(NVGcontext* vg) const
{
	const vec3 dir = normalize(m_endPt - m_startPt);
	const vec3 orthoganalDir = { -dir.y, dir.x, 0 }; // 2D
	const vec3 topLeft = m_startPt + orthoganalDir * m_radius;
	const vec3 bottomLeft = m_startPt - orthoganalDir * m_radius;
	const vec3 topRight = m_endPt + orthoganalDir * m_radius;
	const vec3 bottomRight = m_endPt - orthoganalDir * m_radius;

	nvgFillColor(vg, nvgRGBA(255, 192, 0, 128));
	nvgStrokeColor(vg, nvgRGBA(255, 192, 0, 255));

	nvgBeginPath(vg);
	nvgMoveTo(vg, bottomLeft.x, bottomLeft.y);
	nvgLineTo(vg, bottomRight.x, bottomRight.y);
	nvgLineTo(vg, topRight.x, topRight.y);
	nvgLineTo(vg, topLeft.x, topLeft.y);
	nvgFill(vg);
	nvgStroke(vg);

	nvgBeginPath(vg);
	nvgCircle(vg, m_startPt.x, m_startPt.y, m_radius);
	nvgFill(vg);
	nvgStroke(vg);

	nvgBeginPath(vg);
	nvgCircle(vg, m_endPt.x, m_endPt.y, m_radius);
	nvgFill(vg);
	nvgStroke(vg);

	nvgBeginPath(vg);
	nvgMoveTo(vg, m_startPt.x, m_startPt.y);
	nvgLineTo(vg, m_endPt.x, m_endPt.y);
	nvgStroke(vg);
}

Line Capsule::getShortestLineTo(const Capsule& other) const
{
	vec3 aDir = m_endPt - m_startPt;
	float aMag = length(aDir);
	aDir = normalize(aDir);
	vec3 bDir = other.m_endPt - other.m_startPt;
	float bMag = length(bDir);
	bDir = normalize(bDir);
	vec3 offset = other.m_startPt - m_startPt;

	float denominator = 1 - dot(aDir, bDir) * dot(aDir, bDir);
	float s = (-dot(aDir, bDir) * dot(bDir, offset) + dot(aDir, offset)) / denominator;
	float t = (dot(aDir, bDir) * dot(aDir, offset) - dot(bDir, offset)) / denominator;

	s = glm::clamp(s, 0.0f, aMag);
	t = glm::clamp(t, 0.0f, bMag);

	vec3 closestPtA = m_startPt + aDir * s;
	vec3 closestPtB = other.m_startPt + bDir * t;

	// Reproject clamped values
	s = dot(aDir, closestPtB - m_startPt);
	s = glm::clamp(s, 0.0f, aMag);
	closestPtA = m_startPt + aDir * s;
	t = dot(bDir, closestPtA - other.m_startPt);
	t = glm::clamp(t, 0.0f, bMag);
	closestPtB = other.m_startPt + bDir * t;

	// Remove radii
	vec3 shortestLineDir = closestPtB - closestPtA;
	if (length(shortestLineDir) > (m_radius + other.m_radius)) {
		shortestLineDir = normalize(shortestLineDir);
		closestPtA += shortestLineDir * m_radius;
		closestPtB -= shortestLineDir * other.m_radius;
		return Line{ closestPtA, closestPtB };
	}
	else {
		return Line{};
	}
}
