#include "ContactListener.h"



void ContactListener::BeginContact(b2Contact * contact)
{
	void* bodyUserDataA = contact->GetFixtureA()->GetBody()->GetUserData();
	void* bodyUserDataB = contact->GetFixtureB()->GetBody()->GetUserData();

	if (bodyUserDataA)
		static_cast<Object*>(bodyUserDataA)->startContact(static_cast<Object*>(bodyUserDataB));

	if (bodyUserDataB)
		static_cast<Object*>(bodyUserDataB)->startContact(static_cast<Object*>(bodyUserDataA));
}

void ContactListener::EndContact(b2Contact* contact)
{
	void* bodyUserDataA = contact->GetFixtureA()->GetBody()->GetUserData();
	void* bodyUserDataB = contact->GetFixtureB()->GetBody()->GetUserData();

	if (bodyUserDataA)
		static_cast<Object*>(bodyUserDataA)->endContact(static_cast<Object*>(bodyUserDataB));

	if (bodyUserDataB)
		static_cast<Object*>(bodyUserDataB)->endContact(static_cast<Object*>(bodyUserDataA));

}

void ContactListener::PreSolve(b2Contact* contact, const b2Manifold * oldManifold)
{
	void* bodyUserDataA = contact->GetFixtureA()->GetBody()->GetUserData();
	void* bodyUserDataB = contact->GetFixtureB()->GetBody()->GetUserData();

	if (bodyUserDataA)
		static_cast<Object*>(bodyUserDataA)->preSolve(contact, static_cast<Object*>(bodyUserDataB), contact->GetFixtureB()->GetBody()->GetLinearVelocity()- contact->GetFixtureA()->GetBody()->GetLinearVelocity());

	if (bodyUserDataB)
		static_cast<Object*>(bodyUserDataB)->preSolve(contact, static_cast<Object*>(bodyUserDataA), contact->GetFixtureA()->GetBody()->GetLinearVelocity() - contact->GetFixtureB()->GetBody()->GetLinearVelocity());
}

ContactListener::ContactListener()
{
}


ContactListener::~ContactListener()
{
}
