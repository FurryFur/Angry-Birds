#pragma once

#include "Birb.h"

class NormalBirb : public Birb
{
public:

	NormalBirb(Scene& scene, float posX, float posY, float radius);
	~NormalBirb();
	void Initialize(Scene& scene);
};

