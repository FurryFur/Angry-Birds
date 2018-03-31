#pragma once

#include "Capsule.h"
#include <vector>
#include <glm\vec3.hpp>

#include <memory>

class CapsuleFactory
{
public:
	CapsuleFactory(const CapsuleFactory&) = delete;
	CapsuleFactory(CapsuleFactory&&) = delete;
	~CapsuleFactory();

	static CapsuleFactory& instance();

	void onClick(int button, int action, double mousex, double mousey);
	const std::vector<Capsule>& getCapsuleList() const;

private:
	CapsuleFactory();

	static std::unique_ptr<CapsuleFactory> s_instance;
	
	std::vector<Capsule> m_capsuleList;
	int m_stage;
	int m_curCapsuleIdx;
	glm::vec3 m_startPt;
	glm::vec3 m_endPt;
	float m_radius;
};

