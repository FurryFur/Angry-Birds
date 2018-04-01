#pragma once

#include <Box2D\Box2D.h>

#include "Object.h"

class ContactListener : public b2ContactListener
{
public:
	void BeginContact(b2Contact* contact);
	void EndContact(b2Contact* contact);

	ContactListener();
	~ContactListener();
};

