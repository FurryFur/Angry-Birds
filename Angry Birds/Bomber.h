#pragma once

#include "Birb.h"

class Bomber : public Birb
{
public:
	Bomber(Scene& scene, float posX, float posY, float radius);
	~Bomber();

	void Initialize(Scene& scene) override;

	void startContact(Object*) override;
	void endContact(Object*) override;


private:
	bool m_dead;
};

