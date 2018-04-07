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
	new Birb(*this, 2, 1, .6f);
	new Birb(*this, 3, 1, .6f);
	new Birb(*this, 4, 1, .6f);

	Floor* floor = new Floor(*this, pixelToMeter(WINDOW_WIDTH) / 2, pixelToMeter(WINDOW_HEIGHT) + 2, 100, 10);
	Block* blocky = new Block(*this, 5, 5, 1, 1, CIRCLE, METAL);
	Block* blocky2 = new Block(*this, 5, 4, 1, 1, RECTANGLE, WOOD);
	Block* blocky3 = new Block(*this, 5, 3, 1, 1, RECTANGLE, WOOD);
	Block* blocky4 = new Block(*this, 5, 2, 1, 1, RECTANGLE, WOOD);
	Block* blocky5 = new Block(*this, 1, 10, 1, 1, RECTANGLE, METAL);

	Block* blocky6 = new Block(*this, 10, 20, 5, 1, RECTANGLE, METAL);
	new RevoluteJoint(*this, 10, 20, &blocky6->getBody(), b2_kinematicBody);


	createDistanceJoint(&blocky->getBody(), &blocky2->getBody(), blocky->getBody().GetPosition(), blocky2->getBody().GetPosition(), 1.0f);
	createPrismaticJoint(&floor->getBody(), &blocky5->getBody());



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

std::unique_ptr<Scene> Scene1::createNew() const
{
	return std::unique_ptr<Scene>(new Scene1(m_manager));
}
