#include "SlingLine.h"

#include "Birb.h"
#include "Utils.h"

#include <nanovg.h>

SlingLine::SlingLine(b2Vec2 slingPos, Birb*& grabbedBird)
	: m_slingPos{ slingPos }
	, m_grabbedBird{ grabbedBird }
{

}

void SlingLine::draw(NVGcontext* vg)
{
	if (m_grabbedBird) {
		nvgFillColor(vg, nvgRGBA(255, 192, 0, 128));
		nvgStrokeColor(vg, nvgRGBA(255, 192, 0, 255));
		
		nvgBeginPath(vg);

		const b2Vec2& start = m_grabbedBird->getBody().GetPosition();
		nvgMoveTo(vg, meterToPixel(start.x), meterToPixel(start.y));
		nvgLineTo(vg, meterToPixel(m_slingPos.x), meterToPixel(m_slingPos.y));
		
		nvgStroke(vg);
	}
}
