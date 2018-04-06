#include "Scene1.h"
#include "Utils.h"

#include "Birb.h"
#include "Floor.h"
#include "Block.h"
#include "RevoluteJoint.h"

Scene1::Scene1()
{
	new Birb(*this, 1, 1);
	new Floor(*this, pixelToMeter(WINDOW_WIDTH) / 2, pixelToMeter(WINDOW_HEIGHT) + 2, 100, 10);
	Block* blocky = new Block(*this, 5, 5, 1, 1);
	Block* blocky2 = new Block(*this, 5, 4, 1, 1);

	new RevoluteJoint(*this, 5, 5, &blocky->getBody(), b2_kinematicBody);
	new RevoluteJoint(*this, 5, 4, &blocky2->getBody(), b2_dynamicBody);
}


Scene1::~Scene1()
{
}
