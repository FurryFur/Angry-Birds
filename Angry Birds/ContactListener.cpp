#include "ContactListener.h"



void ContactListener::BeginContact(b2Contact * contact)
{
	//check if fixture A was a birb
	void* bodyUserData = contact->GetFixtureA()->GetBody()->GetUserData();
	if (bodyUserData)
		static_cast<Object*>(bodyUserData)->startContact();

	//check if fixture B was a birb
	bodyUserData = contact->GetFixtureB()->GetBody()->GetUserData();
	if (bodyUserData)
		static_cast<Object*>(bodyUserData)->startContact();
}

void ContactListener::EndContact(b2Contact* contact)
{
	//check if fixture A was a birb
	void* bodyUserData = contact->GetFixtureA()->GetBody()->GetUserData();
	if (bodyUserData)
		static_cast<Object*>(bodyUserData)->endContact();

	//check if fixture B was a birb
	bodyUserData = contact->GetFixtureB()->GetBody()->GetUserData();
	if (bodyUserData)
		static_cast<Object*>(bodyUserData)->endContact();

}

ContactListener::ContactListener()
{
}


ContactListener::~ContactListener()
{
}
