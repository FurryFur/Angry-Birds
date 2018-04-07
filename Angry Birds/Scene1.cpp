#include "Scene1.h"
#include "Utils.h"

#include "Birb.h"
#include "Pig.h"
#include "Floor.h"
#include "Block.h"
#include "RevoluteJoint.h"

Scene1::Scene1(SceneManager& _manager)
	:
	Scene(_manager)
{
	m_levelNumber = 1;

	new Birb(*this, 1, 1, .6f);
	new Floor(*this, pixelToMeter(WINDOW_WIDTH) / 2, pixelToMeter(WINDOW_HEIGHT) + 2, 100, 10);
	Block* blocky = new Block(*this, 5, 5, 1, 1, CIRCLE, METAL);
	Block* blocky2 = new Block(*this, 5, 4, 1, 1, RECTANGLE, WOOD);

	new Pig(*this, 10, 1, .5f);
	new Pig(*this, 11, 1, .5f);
	new Pig(*this, 12, 1, .5f);
	m_pigCount = 3;


	new RevoluteJoint(*this, 5, 5, &blocky->getBody(), b2_kinematicBody);
	new RevoluteJoint(*this, 5, 4, &blocky2->getBody(), b2_dynamicBody);
}


Scene1::~Scene1()
{
}
