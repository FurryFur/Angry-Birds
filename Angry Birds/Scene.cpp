#include "Scene.h"
#include "SceneManager.h"

#include "Birb.h"
#include "Pig.h"
#include "Block.h"
#include "RevoluteJoint.h"
#include "Particle.h"

#include "ContactListener.h"

#include <Box2D\Box2D.h>
#include <sstream>

const float Scene::s_kPixelsPerMeter = 32.0f;
const float Scene::s_kGravity = 10;

Scene::Scene(SceneManager& _manager)
	: m_world{ std::make_unique<b2World>(b2Vec2(0.0f, s_kGravity)) }
	, m_manager(_manager)
{
	m_contactListener = std::make_unique<ContactListener>();
	m_world->SetAllowSleeping(true);
	m_world->SetContinuousPhysics(true);
	m_world->SetContactListener(m_contactListener.get());
}


Scene::~Scene()
{

}

void Scene::update()
{
	static const float32 timeStep = 1.0f / 60.0f;
	static const int32 velocityIterations = 6;
	static const int32 positionIterations = 2;

	m_world->Step(timeStep, velocityIterations, positionIterations);

	removeObjects();

	checkAndEndLevel();
}

void Scene::checkAndEndLevel()
{
	if (m_pigCount <= 0) {
		std::stringstream ss;
		ss << "Level " << (m_levelNumber+1);
		m_manager.loadNewScene(ss.str());
	}
	else if (m_nextFlingableBirbIdx >= m_birbs.size()) {
		// If we have fired all birbs then check if all birbs are stationary
		bool allSleeping = true;
		for (Birb* birb : m_birbs) {
			// Last birb is still grabbed so we shouldn't restart yet
			if (!birb->getBody().IsActive()) {
				allSleeping = false;
				break;
			}

			// Check if moving
			if (birb->getBody().IsAwake() && birb->getBody().GetLinearVelocity().Length() > 1.0f) {
				allSleeping = false;
				break;
			}
		}

		// When all birbs are stationary restart the level
		if (allSleeping) {
			m_manager.restartLevel();
		}
	}
}

b2Body* Scene::addObject(std::unique_ptr<Object> obj)
{
	// Add to birb list if birb
	Birb* birb = dynamic_cast<Birb*>(obj.get());
	if (birb) 
		m_birbs.push_back(birb);

	// Record pig count
	Pig* pig = dynamic_cast<Pig*>(obj.get());
	if (pig)
		++m_pigCount;

	// Create physics body and add to physics simulation
	b2Body* body = m_world->CreateBody(&obj->getBodyDef());

	// Store unique pointer to object
	m_objs.push_back(std::move(obj));

	return body;
}

b2Joint* Scene::createRevoluteJoint(b2Body* bodyA, b2Body* bodyB, b2Vec2 anchorA, b2Vec2 anchorB, bool spin, float motorSpeed)
{
	b2RevoluteJointDef revoluteJointDef;
	revoluteJointDef.bodyA = bodyA;
	revoluteJointDef.bodyB = bodyB;
	revoluteJointDef.collideConnected = false;
	revoluteJointDef.localAnchorA.Set(anchorA.x, anchorA.y);
	revoluteJointDef.localAnchorB.Set(anchorB.x, anchorB.y);

	revoluteJointDef.enableLimit = !spin;
	revoluteJointDef.lowerAngle = -45 * g_kDegToRad;
	revoluteJointDef.upperAngle = 45 * g_kDegToRad;

	revoluteJointDef.enableMotor = spin;
	revoluteJointDef.maxMotorTorque = 100.0f;
	revoluteJointDef.motorSpeed = motorSpeed;
	

	return m_world->CreateJoint(&revoluteJointDef);;
}

// TODO: MAKE MORE CUSTOMIZABLE
b2Joint* Scene::createDistanceJoint(b2Body* bodyA, b2Body* bodyB, b2Vec2 anchorA, b2Vec2 anchorB, float length)
{
	b2DistanceJointDef distanceJointDef;
	distanceJointDef.Initialize(bodyA, bodyB, anchorA, anchorB);
	//distanceJointDef.frequencyHz = 4.0f;
	//d//istanceJointDef.dampingRatio = 0.1f;
	distanceJointDef.length = length;
	distanceJointDef.collideConnected = true;
	return m_world->CreateJoint(&distanceJointDef);
}

// TODO: MAKE MORE CUSTOMIZABLE
b2Joint* Scene::createPrismaticJoint(b2Body* bodyA, b2Body* bodyB, float lower, float upper)
{
	b2PrismaticJointDef prismaticJointDef;

	prismaticJointDef.Initialize(bodyA, bodyB, bodyB->GetPosition(), b2Vec2(-1, 0));
	prismaticJointDef.lowerTranslation = lower;
	prismaticJointDef.upperTranslation = upper;
	prismaticJointDef.enableLimit = true;
	prismaticJointDef.maxMotorForce = 1000;
	prismaticJointDef.motorSpeed = 1.0f;
	prismaticJointDef.enableMotor = true;
	return m_world->CreateJoint(&prismaticJointDef);
}

Block* Scene::createRopeStructure(Scene& scene, float xPos, float yPos, int chainLinks, float width, float height)
{
	Block* nooseBase = new Block(*this, xPos, yPos, width, height, RECTANGLE, WOOD);
	Hinge* nooseHinge = new Hinge(scene, xPos, yPos, b2_kinematicBody);

	createRevoluteJoint(&nooseHinge->getBody(), &nooseBase->getBody(), b2Vec2(0, 0), b2Vec2(0, 0), false, 0.0f);
	Block* previousLink = nooseBase;

	for (int i = 0; i < chainLinks; i++)
	{
		Block* currentLink = new Block(*this, xPos, yPos + 1 + i, width, height, RECTANGLE, WOOD);
		createRevoluteJoint(&previousLink->getBody(), &currentLink->getBody(), b2Vec2(0, 0), b2Vec2(0, -1.0), false, 0.0f);
		previousLink = currentLink;
	}

	return previousLink;
}

void Scene::createExplosion(int rays, float blastPower, b2Vec2 center, bool shrapnel)
{
	for (int i = 0; i < rays; i++) {
		float angle = (i / (float)rays) * 360 * g_kDegToRad;
		b2Vec2 rayDir(sinf(angle), cosf(angle));

		Particle* particle = new Particle(*this, center.x, center.y, blastPower,rayDir, rays, shrapnel);
		//Block* block = new Block(*this, 10, 10, 1, 1, (Shape)(rand() % 2), WOOD);

	}
}

void Scene::removeObjects()
{
	// Remove sleeping particles
	for (unsigned int i = 0; i < m_objs.size(); i++)
	{
		if (dynamic_cast<Particle*>(m_objs[i].get()) != nullptr && !m_objs[i]->getBody().IsAwake())
		{
			m_world->DestroyBody(&m_objs[i]->getBody());
			m_objs.erase(m_objs.begin() + i);
		}
	}

	if (m_killList.size() != 0)
	{
		for (auto& kill : m_killList)
		{
			if (dynamic_cast<Pig*>(kill) != nullptr) {
				m_pigCount--;
			}
			else if(dynamic_cast<Birb*>(kill) != nullptr)
			{
				createExplosion(20, 100, kill->getBody().GetPosition(), false);
				createExplosion(10, 10, kill->getBody().GetPosition(), true);

				m_birbs.erase(std::remove_if(m_birbs.begin(), m_birbs.end(),
					[kill](Birb* &birb) {return birb == kill; }),
					m_birbs.end());

				m_nextFlingableBirbIdx--;
			}

			m_world->DestroyBody(&kill->getBody());
			m_objs.erase(std::remove_if(m_objs.begin(), m_objs.end(), 
				[kill](std::unique_ptr<Object> &obj) {return obj.get() == kill; }),
				m_objs.end());

			kill = nullptr;
		}

		m_killList.clear();
	}
}

void Scene::addToKillList(Object* toKill)
{
	m_killList.push_back(toKill);
}

void Scene::draw(NVGcontext* vg)
{
	for (auto& obj : m_objs) {

		if(obj)
			obj->draw(vg);
	}
}

int Scene::getLevelNum() const
{
	return m_levelNumber;
}

Birb* Scene::getNextFlingableBirb()
{
	// Get the next flingable birb in the scene
	Birb* nextBirb = nullptr;
	if (m_nextFlingableBirbIdx < m_birbs.size()) {
		nextBirb = m_birbs[m_nextFlingableBirbIdx];
		++m_nextFlingableBirbIdx;
	}

	return nextBirb;
}