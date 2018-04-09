#pragma once

#include <Box2D\Box2D.h>

#include "Object.h"

class ContactListener : public b2ContactListener
{
public:
	void BeginContact(b2Contact* contact) override;
	void EndContact(b2Contact* contact) override;
	void PreSolve(b2Contact* contact, const b2Manifold* oldManifold) override;

	ContactListener();
	~ContactListener();
};

