#pragma once

#include <glm\vec3.hpp>

struct NVGcontext;
class Line;

class Capsule
{
public:
	Capsule(const glm::vec3& startPt = { 0,0,0 }, const glm::vec3& endPt = { 0,0,0 }, float radius = 30);
	~Capsule();

	glm::vec3 m_startPt;
	glm::vec3 m_endPt;
	float m_radius;

	void draw(NVGcontext*) const;
	Line getShortestLineTo(const Capsule&) const;
};

