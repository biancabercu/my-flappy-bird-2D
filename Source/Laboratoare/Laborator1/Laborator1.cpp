#include "Laborator1.h"

#include <vector>
#include <iostream>

#include <Core/Engine.h>
#define RADIUS 5
using namespace std;
int x = 0, y = 0, z = 0;
int moveObject = 0;
int nrNextObj = 0;
int angle = 0;
// Order of function calling can be seen in "Source/Core/World.cpp::LoopUpdate()"
// https://github.com/UPB-Graphics/Framework-EGC/blob/master/Source/Core/World.cpp

Laborator1::Laborator1()
{
}

Laborator1::~Laborator1()
{
}

void Laborator1::Init()
{
	// Load a mesh from file into GPU memory
	{
		Mesh* mesh = new Mesh("box");
		mesh->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "box.obj");
		meshes[mesh->GetMeshID()] = mesh;

		Mesh* teapotMesh = new Mesh("teapot");
		teapotMesh->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "teapot.obj");
		meshes[teapotMesh->GetMeshID()] = teapotMesh;

		Mesh* sphereMesh = new Mesh("sphere");
		sphereMesh->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "sphere.obj");
		meshes[sphereMesh->GetMeshID()] = sphereMesh;
	}
}

void Laborator1::FrameStart()
{

}

void Laborator1::Update(float deltaTimeSeconds)
{
	glm::ivec2 resolution = window->props.resolution;

	// sets the clear color for the color buffer
	glClearColor(0, 0, 0, 1);

	// clears the color buffer (using the previously set color) and depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// sets the screen area where to draw
	glViewport(0, 0, resolution.x, resolution.y);
	//x rosu, y verde, z albastru
	// render the object
	RenderMesh(meshes["box"], glm::vec3(1, 0.5f, 0), glm::vec3(0.5f));
	
	//render my own another obj
	RenderMesh(meshes["teapot"], glm::vec3(2, 0.5f, 0));

	RenderMesh(meshes["sphere"], glm::vec3(2, 2, 1 ), glm::vec3(0.05f));

	//alternating between 3 obj 
	//sphere-box-teapot?
	if (nrNextObj % 3 == 0) {
		RenderMesh(meshes["sphere"], glm::vec3(-2, 0.5f, 1), glm::vec3(1));
	}
	else {
		if (nrNextObj % 3 == 1) {
			RenderMesh(meshes["box"], glm::vec3(-2, 0.5f, 1), glm::vec3(1));
		}
		else {
			RenderMesh(meshes["teapot"], glm::vec3(-2, 0.5f, 1), glm::vec3(0.5f));
		}
	}

	// render the object again but with different properties
	RenderMesh(meshes["box"], glm::vec3(-1 + x, 0.5f + y, 0 + z));	//continuam aici partea in care obiectul se misca
	//direct se poate misca, fara vreo tasta de permisiune
	if (window->KeyHold(GLFW_KEY_Q)) {
		x += 2 * deltaTimeSeconds;
	}
	if (window->KeyHold(GLFW_KEY_A)) {
		x -= 2 * deltaTimeSeconds;
	}
	if (window->KeyHold(GLFW_KEY_W)) {
		y += 2 * deltaTimeSeconds;
	}
	if (window->KeyHold(GLFW_KEY_S)) {
		y -= 2 * deltaTimeSeconds;
	}
	if (window->KeyHold(GLFW_KEY_E)) {
		z += 2 * deltaTimeSeconds;
	}
	if (window->KeyHold(GLFW_KEY_D)) {
		z -= 2 * deltaTimeSeconds;
	}

}
void Laborator1::FrameEnd()
{
	DrawCoordinatSystem();
}

// Read the documentation of the following functions in: "Source/Core/Window/InputController.h" or
// https://github.com/UPB-Graphics/Framework-EGC/blob/master/Source/Core/Window/InputController.h

void Laborator1::OnInputUpdate(float deltaTime, int mods)
{
	// treat continuous update based on input
};

void Laborator1::OnKeyPress(int key, int mods)
{
	// add key press event
	if (key == GLFW_KEY_F) {
		glClearColor(1, 0, 0, 1);
	}
	if (key == GLFW_KEY_G) {
		nrNextObj++;
	}

	//folosim o tasta ca sa permitem ca box-ul sa se miste
	//de exemplu P
	if (key == GLFW_KEY_P) {
		moveObject=1;
	}
	//asadar folosind taste?
	if (moveObject != 0) {
		if (key == GLFW_KEY_Q) {
			//x++;
		}
		if (key == GLFW_KEY_A) {
			//x--;
		}
		if (key == GLFW_KEY_W) {
			//z++;
		}
		if (key == GLFW_KEY_S) {
			//z--;
		}
		if (key == GLFW_KEY_E) {
			//y++;
		}
		if (key == GLFW_KEY_D) {
			//y--;
		}
	}
};

void Laborator1::OnKeyRelease(int key, int mods)
{
	// add key release event
	if (key == GLFW_KEY_F) {
		glClearColor(0, 0, 0, 1);
	}

	if (key == GLFW_KEY_P) {
		moveObject = 0;
	}
};

void Laborator1::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
	// add mouse move event
};

void Laborator1::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button press event
};

void Laborator1::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button release event
}

void Laborator1::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
	// treat mouse scroll event
}

void Laborator1::OnWindowResize(int width, int height)
{
	// treat window resize event
}
