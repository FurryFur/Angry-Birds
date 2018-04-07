#pragma once

#include "Scene.h"

#include <Box2D\Box2D.h>

#define WINDOW_WIDTH 1600
#define WINDOW_HEIGHT 800

struct Vec3
{
	float x, y, z;
};

static float pixelToMeter(float pixel)
{
	return pixel / Scene::s_kPixelsPerMeter;
}
 
static float meterToPixel(float pixel)
{
	return pixel * Scene::s_kPixelsPerMeter;
}

// Limit a vector to a specified magnitude
static b2Vec2 limitVec(const b2Vec2& vec, float magLimit)
{
	float mag = vec.Length();
	if (mag > magLimit) {
		b2Vec2 newVec = vec;
		newVec.Normalize();
		newVec *= magLimit;
		return newVec;
	}
	else {
		return vec;
	}
}