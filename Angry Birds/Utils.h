#pragma once

#include "Scene.h"

#include <Box2D\Box2D.h>

#include <glm\gtc\constants.hpp>

#define WINDOW_WIDTH 1600
#define WINDOW_HEIGHT 800

const float g_kDegToRad = glm::pi<float>() / 180.0f;

struct Color
{
	unsigned char x, y, z;
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

static float randFloat(float min, float max)
{
	return min + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (max - min)));
}