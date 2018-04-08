#include "Scene2.h"
#include "Utils.h"

#include "Birb.h"
#include "Pig.h"
#include "Floor.h"
#include "Block.h"
#include "RevoluteJoint.h"

Scene2::Scene2(SceneManager& _manager)
	:
	Scene(_manager)
{
	m_levelNumber = 2;

	new Birb(*this, 1, 1, .6f);
	new Birb(*this, 2, 1, .6f);
	new Birb(*this, 3, 1, .6f);
	new Birb(*this, 4, 1, .6f);

	float meterWidth = pixelToMeter(WINDOW_WIDTH);
	float meterHeight = pixelToMeter(WINDOW_HEIGHT);
	float midScreenX = pixelToMeter(WINDOW_WIDTH) / 2;
	float midScreenY = pixelToMeter(WINDOW_HEIGHT) / 2;


	// Box of the level
	Floor* groundFloor = new Floor(*this, meterWidth / 2, meterHeight + 49.0f, meterWidth, 100);
	Floor* upperWall = new Floor(*this, meterWidth / 2, -49.0f, meterWidth, 100);
	Floor* leftWall = new Floor(*this, -49.9f, 0 + meterHeight / 2, 100, meterHeight - 2);
	Floor* rightWall = new Floor(*this, meterWidth + 49.9f, 0 + meterHeight / 2, 100, meterHeight - 2);

	// Wall
	for (int i = 0; i < 15; i++)
	{
		Block* wall = new Block(*this, (meterWidth - 10) - i*2, meterHeight - 3.5f, 1, 0.5f + (i * 0.5f), RECTANGLE, WOOD);

	}

	Pig* noosedPig = new Pig(*this, meterWidth - 1, midScreenY, .5f);
}


Scene2::~Scene2()
{
}

std::unique_ptr<Scene> Scene2::createNew() const
{
	return std::unique_ptr<Scene>(new Scene2(m_manager));
}
