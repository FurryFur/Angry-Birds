#pragma once

struct b2BodyDef;
struct NVGcontext;

class Object
{
public:
	virtual ~Object() {};

	virtual void draw(NVGcontext*) const = 0;
	virtual const b2BodyDef& getBodyDef() const = 0;

	virtual void startContact() = 0;
	virtual void endContact() = 0;
};

