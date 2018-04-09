#pragma once

#include "Birb.h"

class StrikeBirb : public Birb
{
public:
	StrikeBirb(Scene& scene, float posX, float posY, float radius);
	~StrikeBirb() override;

	// Inherited via Birb
	virtual void Initialize(Scene& scene) override;
	virtual void draw(NVGcontext*) const override;

	bool inFlight;

	void startContact(Object* other) override;
};

