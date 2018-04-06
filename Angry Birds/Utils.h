#pragma once

#include "Scene.h"

#define WINDOW_WIDTH 1600
#define WINDOW_HEIGHT 800

static float pixelToMeter(float pixel)
{
	return pixel / Scene::s_kPixelsPerMeter;
}
 
static float meterToPixel(float pixel)
{
	return pixel * Scene::s_kPixelsPerMeter;
}