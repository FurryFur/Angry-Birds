#pragma once

#include <glm\vec3.hpp>

struct NVGcontext;


class Line
{
public:
	Line(const glm::vec3& startPt = { 0, 0, 0 }, const glm::vec3& endPt = { 0, 0, 0 });
	~Line();

	void draw(NVGcontext*) const;

	glm::vec3 m_startPt;
	glm::vec3 m_endPt;
};

