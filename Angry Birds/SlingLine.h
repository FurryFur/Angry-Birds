#pragma once

#include <Box2D\Box2D.h>

class Birb;
struct NVGcontext;

class SlingLine {
public:
	SlingLine(b2Vec2 slingPos, Birb*& grabbedBird);
	void draw(NVGcontext*);
	
private:
	b2Vec2 m_slingPos;
	Birb*& m_grabbedBird;
};