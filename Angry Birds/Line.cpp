#include "Line.h"

#include <nanovg.h>

Line::Line(const glm::vec3& startPt, const glm::vec3& endPt)
	: m_startPt{ startPt }
	, m_endPt{ endPt }
{
}

Line::~Line()
{
}

void Line::draw(NVGcontext* vg) const
{
	nvgStrokeColor(vg, nvgRGBA(0, 100, 255, 255));

	nvgBeginPath(vg);
	nvgMoveTo(vg, m_startPt.x, m_startPt.y);
	nvgLineTo(vg, m_endPt.x, m_endPt.y);
	nvgStroke(vg);
}
