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
	new Floor(*this, pixelToMeter(WINDOW_WIDTH) / 2, pixelToMeter(WINDOW_HEIGHT) + 2, 100, 10);
}


Scene2::~Scene2()
{
}
