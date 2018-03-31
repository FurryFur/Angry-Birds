#include "CapsuleFactory.h"

#include <GLFW\glfw3.h>
#include <glm\glm.hpp>

using namespace glm;

std::unique_ptr<CapsuleFactory> CapsuleFactory::s_instance = nullptr;

CapsuleFactory::CapsuleFactory()
	: m_stage{ 0 }
{
}

CapsuleFactory::~CapsuleFactory()
{
}

CapsuleFactory& CapsuleFactory::instance()
{
	if (!s_instance)
		s_instance = std::unique_ptr<CapsuleFactory>(new CapsuleFactory());
	return *s_instance;
}

void CapsuleFactory::onClick(int button, int action, double mousex, double mousey)
{
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
		vec3 mousePt = { mousex, mousey, 0 };

		switch (m_stage) {
		case 0:
			m_startPt = mousePt;
			break;
		case 1:
			m_radius = glm::length(mousePt - m_startPt);
			break;
		case 2:
			m_endPt = mousePt;
			if (m_capsuleList.size() < 2)
				m_capsuleList.push_back({ m_startPt, m_endPt, m_radius });
			else
				m_capsuleList.at(m_curCapsuleIdx) = { m_startPt, m_endPt, m_radius };
			break;
		}

		m_stage = (m_stage + 1) % 3;
		if (m_stage == 0)
			m_curCapsuleIdx = (m_curCapsuleIdx + 1) % 2;
	}
		
}

const std::vector<Capsule>& CapsuleFactory::getCapsuleList() const
{
	return m_capsuleList;
}
