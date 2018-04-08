//
// Copyright (c) 2013 Mikko Mononen memon@inside.org
//
// This software is provided 'as-is', without any express or implied
// warranty.  In no event will the authors be held liable for any damages
// arising from the use of this software.
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it
// freely, subject to the following restrictions:
// 1. The origin of this software must not be misrepresented; you must not
//    claim that you wrote the original software. If you use this software
//    in a product, an acknowledgment in the product documentation would be
//    appreciated but is not required.
// 2. Altered source versions must be plainly marked as such, and must not be
//    misrepresented as being the original software.
// 3. This notice may not be removed or altered from any source distribution.
//


#include "Birb.h"
#include "Floor.h"
#include "Block.h"
#include "Utils.h"
#include "SlingLine.h"

#include "Scene.h"
#include "Scene1.h"
#include "Scene2.h"
#include "SceneManager.h"

#include <Box2D\Box2D.h>
#include <glm\glm.hpp>
#include <glad\glad.h>
#include <GLFW\glfw3.h>
#include <nanovg.h>
#define NANOVG_GL3_IMPLEMENTATION
#include <nanovg_gl.h>

#include <memory>

using namespace glm;

Birb* g_grabbedBirb = nullptr;
SceneManager g_sceneManager;

const b2Vec2 g_kSlingshotPos = { pixelToMeter(200), pixelToMeter(WINDOW_HEIGHT - 150) };

void errorcb(int error, const char* desc)
{
	printf("GLFW error %d: %s\n", error, desc);
}

void key(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}

// Make grabbed birb follow mouse position
void mouseMoveCallback(GLFWwindow* window, double mousex, double mousey)
{
	if (g_grabbedBirb) {
		b2Vec2 mousePos = { pixelToMeter(mousex), pixelToMeter(mousey) };
		b2Vec2 offsetFromSlingshot = mousePos - g_kSlingshotPos;
		offsetFromSlingshot = limitVec(offsetFromSlingshot, 2);
		b2Vec2 newBirbPos = g_kSlingshotPos + offsetFromSlingshot;

		b2Body& body = g_grabbedBirb->getBody();
		body.SetTransform(newBirbPos, body.GetAngle());
		body.SetLinearVelocity(b2Vec2{ 0, 0 });
		body.SetAngularVelocity(0);
	}
}

// Grab birb on mouse down, release on mouse up
void mouseBtnCallback(GLFWwindow* window, int button, int action, int mods) 
{
	if (action == GLFW_PRESS) {
		Birb* birb = g_sceneManager.getCurrentScene()->getNextFlingableBirb();
		if (birb) {
			// Make birb follow mouse 
			birb->getBody().SetActive(false);
			g_grabbedBirb = birb;

			double mousex, mousey;
			glfwGetCursorPos(window, &mousex, &mousey);
			mouseMoveCallback(window, mousex, mousey);
		}
	}

	if (g_grabbedBirb && action == GLFW_RELEASE) {
		g_grabbedBirb->getBody().SetActive(true);
		const b2Vec2& birbPos = g_grabbedBirb->getBody().GetPosition();
		b2Vec2 impulse = (g_kSlingshotPos - birbPos);
		impulse *= 60;
		g_grabbedBirb->getBody().ApplyLinearImpulse(impulse, birbPos, true);

		g_grabbedBirb = nullptr;
	}
}

int main()
{
	GLFWwindow* window;
	NVGcontext* vg = NULL;


	if (!glfwInit()) {
		printf("Failed to init GLFW.");
		return -1;
	}

	glfwSetErrorCallback(errorcb);
#ifndef _WIN32 // don't require this on win32, and works with more cards
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#endif
	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, 1);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "NanoVG", NULL, NULL);
	//	window = glfwCreateWindow(1000, 600, "NanoVG", glfwGetPrimaryMonitor(), NULL);
	if (!window) {
		glfwTerminate();
		return -1;
	}

	glfwSetMouseButtonCallback(window, mouseBtnCallback);
	glfwSetCursorPosCallback(window, mouseMoveCallback);
	glfwSetKeyCallback(window, key);

	glfwMakeContextCurrent(window);
	gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
	glfwSwapInterval(1);

	vg = nvgCreateGL3(NVG_ANTIALIAS | NVG_STENCIL_STROKES | NVG_DEBUG);
	if (vg == NULL) {
		printf("Could not init nanovg.\n");
		return -1;
	}

	// Create a scene with some Birbs
	auto scene2 = std::unique_ptr<Scene>(new Scene2(g_sceneManager));
	g_sceneManager.addScene(std::move(scene2), "Level 2");

	auto scene1 = std::unique_ptr<Scene>(new Scene1(g_sceneManager));
	g_sceneManager.addScene(std::move(scene1), "Level 1");



	SlingLine slingLineDrawer(g_kSlingshotPos, g_grabbedBirb);
	 
	while (!glfwWindowShouldClose(window)) {
		int winWidth, winHeight;
		int fbWidth, fbHeight;
		float pxRatio;

		glfwGetWindowSize(window, &winWidth, &winHeight);
		glfwGetFramebufferSize(window, &fbWidth, &fbHeight);
		// Calculate pixel ration for hi-dpi devices.
		pxRatio = (float)fbWidth / (float)winWidth;

		// Update and render
		glViewport(0, 0, fbWidth, fbHeight);
		glClearColor(0.3f, 0.3f, 0.32f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

		nvgBeginFrame(vg, winWidth, winHeight, pxRatio);

		slingLineDrawer.draw(vg);
		g_sceneManager.getCurrentScene()->update();
		g_sceneManager.getCurrentScene()->draw(vg);

		nvgEndFrame(vg);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	nvgDeleteGL3(vg);

	glfwTerminate();
	return 0;
}