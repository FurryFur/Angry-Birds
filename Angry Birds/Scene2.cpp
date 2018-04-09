#include "Scene2.h"
#include "Utils.h"

#include "Birb.h"
#include "NormalBirb.h"
#include "Pig.h"
#include "Floor.h"
#include "Block.h"
#include "RevoluteJoint.h"

Scene2::Scene2(SceneManager& _manager)
	:
	Scene(_manager)
{
	m_levelNumber = 2;

	new NormalBirb(*this, 1, 1, .6f);
	new NormalBirb(*this, 2, 1, .6f);
	new NormalBirb(*this, 3, 1, .6f);
	new NormalBirb(*this, 4, 1, .6f);

	float meterWidth = pixelToMeter(WINDOW_WIDTH);
	float meterHeight = pixelToMeter(WINDOW_HEIGHT);
	float midScreenX = pixelToMeter(WINDOW_WIDTH) / 2;
	float midScreenY = pixelToMeter(WINDOW_HEIGHT) / 2;


	// Box of the level
	Floor* groundFloor = new Floor(*this, meterWidth / 2, meterHeight + 49.0f, meterWidth, 100);
	Floor* upperWall = new Floor(*this, meterWidth / 2, -49.0f, meterWidth, 100);
	Floor* leftWall = new Floor(*this, -49.9f, 0 + meterHeight / 2, 100, meterHeight - 2);
	Floor* rightWall = new Floor(*this, meterWidth + 49.9f, 0 + meterHeight / 2, 100, meterHeight - 2);

	float floorOffset = 1.0f;

	Block* metalCircle = new Block(*this, midScreenX, midScreenY, 2, 2, CIRCLE, METAL);
	Hinge* circleHinge = new Hinge(*this, midScreenX, midScreenY, b2_kinematicBody);
	createRevoluteJoint(&metalCircle->getBody(), &circleHinge->getBody(), b2Vec2(0,0), b2Vec2(0, 0), true, 100.0f);

	for (int i = 0; i < 4; i++)
	{
		Pig* pigOnCircle = new Pig(*this, midScreenX + (3 * cos(i * 90 * g_kDegToRad)), midScreenY + (3 * sin(i * 90 * g_kDegToRad)), .5f);
		createDistanceJoint(&metalCircle->getBody(), &pigOnCircle->getBody(), pigOnCircle->getBody().GetPosition() + b2Vec2(0, 0), pigOnCircle->getBody().GetPosition() + b2Vec2(0.0f, 0.0f),0.5f);
	}

	// Wall
	for (int i = 0; i < 15; i++)
	{
		float yScale = 0.5f + (i * 0.5f);
		Block* wall = new Block(*this, (meterWidth - 10) - i * 2, (meterHeight - yScale / 2) - floorOffset, 1, yScale, RECTANGLE, WOOD);
		if (i % 2 == 0) {
			Block* noosedPig = new Block(*this, (meterWidth - 10) - i * 2, meterHeight - yScale - floorOffset - .5f, 0.5f, 0.5f, CIRCLE, METAL);
		}
	}

	Pig* genericPig1 = new Pig(*this, meterWidth - 1, midScreenY, .5f);
	Pig* genericPig2 = new Pig(*this, meterWidth - 2, midScreenY, .5f);
	Pig* genericPig3 = new Pig(*this, meterWidth - 1.5f, midScreenY -1, .5f);

}


Scene2::~Scene2()
{
}

std::unique_ptr<Scene> Scene2::createNew() const
{
	return std::unique_ptr<Scene>(new Scene2(m_manager));
}
