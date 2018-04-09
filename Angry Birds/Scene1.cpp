#include "Scene1.h"
#include "Utils.h"

#include "Birb.h"
#include "BomberBirb.h"
#include "NormalBirb.h"
#include "StrikeBirb.h"
#include "Pig.h"
#include "Floor.h"
#include "Block.h"
#include "RevoluteJoint.h"

Scene1::Scene1(SceneManager& _manager)
	:
	Scene(_manager)
{
	m_levelNumber = 1;

	new StrikeBirb(*this, 4, 1, .6f);
	new Bomber(*this, 3, 1, .6f);
	new Bomber(*this, 2, 1, .6f);
	new NormalBirb(*this, 1, 1, .6f);

	float meterWidth = pixelToMeter(WINDOW_WIDTH);
	float meterHeight = pixelToMeter(WINDOW_HEIGHT);
	float midScreenX = pixelToMeter(WINDOW_WIDTH) / 2;
	float midScreenY = pixelToMeter(WINDOW_HEIGHT) / 2;

	// Box of the level
	Floor* groundFloor = new Floor(*this, meterWidth / 2, meterHeight + 49.0f, meterWidth, 100);
	Floor* upperWall =   new Floor(*this, meterWidth / 2, -49.0f, meterWidth, 100);
	Floor* leftWall =  new Floor(*this, -49.9f, 0 + meterHeight / 2, 100, meterHeight - 2);
	Floor* rightWall = new Floor(*this, meterWidth + 49.9f, 0 + meterHeight / 2, 100, meterHeight - 2);

	// Generate random pile of blocks around pigs
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			Block* block = new Block(*this, meterWidth - 3.0f - j, 6.0f - i, randFloat(0.3f, 0.6f), randFloat(0.3f, 0.6f), (Shape)(rand() % 2), WOOD);
			if(rand() % 10 < 1)
				Pig* noosedPig = new Pig(*this, (meterWidth - 3.0f - j), 6.0f - i, .5f);
		}
	}

	Block* garbageWall = new Block(*this, meterWidth - 9, 0 + 6, 1, 10, RECTANGLE, WOOD);
	Hinge* garbageHinge = new Hinge(*this, meterWidth - 9, 0 + 6, b2_kinematicBody);
	createRevoluteJoint(&garbageHinge->getBody(), &garbageWall->getBody(), b2Vec2(0, 0), b2Vec2(0, 0), false, 0.0f);

	Block* garbageFloor = new Block(*this, meterWidth - 4.75f, 11.5f, 9.0f, 1, RECTANGLE, WOOD);
	createPrismaticJoint(&groundFloor->getBody(), &garbageFloor->getBody(), -8.5f,8.5f);

	// Seesaw
	Block* seeSaw = new Block(*this, midScreenX, midScreenY, 1, 10, RECTANGLE, METAL);
	Hinge* seeSawHinge = new Hinge(*this, midScreenX, midScreenY + 2, b2_kinematicBody);
	createRevoluteJoint(&seeSawHinge->getBody(), &seeSaw->getBody(), b2Vec2(0, 0), b2Vec2(0, 0), true, 500.0f);

	// Noosed pig
	int chainLink = 7;

	for (int i = 0; i < 3; i++)
	{
		Block* lastLink = createRopeStructure(*this, (midScreenX - 3) + i*3, 1.5f, chainLink, 0.3f, 1);
		Pig* noosedPig = new Pig(*this, (midScreenX - 6) + i * 3, 1.5f + chainLink, .5f);
		createRevoluteJoint(&lastLink->getBody(), &noosedPig->getBody(), b2Vec2(0, 1), b2Vec2(0, 0), false, 0.0f);
	}
}


Scene1::~Scene1()
{
}

std::unique_ptr<Scene> Scene1::createNew() const
{
	return std::unique_ptr<Scene>(new Scene1(m_manager));
}
