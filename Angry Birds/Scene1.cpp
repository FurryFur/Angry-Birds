#include "Scene1.h"

#include "Birb.h"
#include "Floor.h"

Scene1::Scene1()
{
	new Birb(*this, 1, 1);
	new Floor(*this, 2.1f, 10, 2, 1);
}


Scene1::~Scene1()
{
}
