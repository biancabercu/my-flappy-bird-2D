#include <vector>
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <Core/Engine.h>

#include "Tema1.h"
#include "Transform2D.h"
#include "Object2D.h"

using namespace std;

Tema1::Tema1()
{
}

Tema1::~Tema1()
{
}

void Tema1::Init()
{
	glm::ivec2 resolution = window->GetResolution();
	auto camera = GetSceneCamera();
	camera->SetOrthographic(0, (float)resolution.x, 0, (float)resolution.y, 0.01f, 400);
	camera->SetPosition(glm::vec3(0, 0, 50));
	camera->SetRotation(glm::vec3(0, 0, 0));
	camera->Update();
	GetCameraInput()->SetActive(false);

	glm::vec3 corner = glm::vec3(0, 0, 0);
	glm::vec2 windowSize = window->GetResolution();
	float wingLength = 30;
	float bodyRadius = 30;

	glisUpWall = resolution.y;
	glisDownWall = 0;

	// initialize angularStep
	angularStep = 0;
	for (int i = 0; i < 7; i++) {
		lower[i] = (rand() % 15 + 5) * 0.1;
		upper[i] = 2 - lower[i];
		cout << lower[i] << " " << upper[i] << "\n";
		wallOffsets[i] = 0;
		betweenOffsets[i] = 0.14 * resolution.x;;
	}


	Mesh* circle = Object2D::CreateCircle("circle", corner, 15, 10000, glm::vec3(0.7, 0.3, 0), true);
	AddMeshToList(circle);
	Mesh* beak = Object2D::CreateTriangle("beak", corner, 10, glm::vec3(0.9, 0.7, 0), true);
	AddMeshToList(beak);
	Mesh* feather = Object2D::CreateTriangle("feather", corner, 10, glm::vec3(1, 1, 1), true);
	AddMeshToList(feather);
	Mesh* eyesWhite = Object2D::CreateCircle("eyesWhite", corner, 15 / 2, 10000, glm::vec3(1, 1, 1), true);
	AddMeshToList(eyesWhite);
	Mesh* eyesColor = Object2D::CreateCircle("eyesColor", corner, 15 / 4, 10000, glm::vec3(0.2, 0, 0.9), true);
	AddMeshToList(eyesColor);

	brickWidth = windowSize.x * 0.05;
	brickHeight = windowSize.y * 0.25;
	Mesh* brick = Object2D::CreateRectangle("brick", corner, brickWidth, brickHeight, glm::vec3(0.6, 0, 0.2), true);
	AddMeshToList(brick);
}
void Tema1::FrameStart()
{
	// clears the color buffer (using the previously set color) and depth buffer
	glClearColor(0, 0, 0.3, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::ivec2 resolution = window->GetResolution();
	// sets the screen area where to draw
	glViewport(0, 0, resolution.x, resolution.y);
}

void Tema1::Update(float deltaTimeSeconds)
{
	glLineWidth(10);
	glm::ivec2 resolution = window->GetResolution();
	//translateX += deltaTimeSeconds * 100;
	//translateY += deltaTimeSeconds * 50.f;
	//angularStep += deltaTimeSeconds * 2.f;

	angleMatrix = glm::mat3(1);
	if (waitStart == FALSE) {
		if (startFlying == FALSE && (gravity + up + resolution.y / 2 - 10) != 0) {
			gravity -= 6;
			angleMatrix *= Transform2D::Rotate(-50);
		}
		if (startFlying == TRUE) {
			up += 6;
			angleMatrix *= Transform2D::Rotate(50);
		}
	}

	//WING
	//FEATHERS
	modelMatrix = glm::mat3(1);
	modelMatrix *= Transform2D::Translate(resolution.x * 0.25 + 25 + one, gravity + up + resolution.y / 2 + one);
	modelMatrix *= angleMatrix;
	modelMatrix *= Transform2D::Rotate(-0.785398);
	RenderMesh2D(meshes["feather"], shaders["VertexColor"], modelMatrix);

	modelMatrix = glm::mat3(1);
	modelMatrix *= Transform2D::Translate(resolution.x * 0.25 + 25 + one, gravity + up + resolution.y / 2 - 5 + one);
	modelMatrix *= angleMatrix;
	modelMatrix *= Transform2D::Rotate(-0.785398);
	RenderMesh2D(meshes["feather"], shaders["VertexColor"], modelMatrix);

	modelMatrix = glm::mat3(1);
	modelMatrix *= Transform2D::Translate(resolution.x * 0.25 + 25 + one, gravity + up + resolution.y / 2 - 10 + one);
	modelMatrix *= Transform2D::Rotate(-0.785398);
	modelMatrix *= angleMatrix;
	modelMatrix *= Transform2D::Scale(2, 2);
	RenderMesh2D(meshes["beak"], shaders["VertexColor"], modelMatrix);

	modelMatrix = glm::mat3(1);
	modelMatrix *= Transform2D::Translate(resolution.x * 0.25 + 25 + one, gravity + up + resolution.y / 2 - 10 + one);
	modelMatrix *= Transform2D::Rotate(-1.0472);
	modelMatrix *= angleMatrix;
	modelMatrix *= Transform2D::Scale(2, 2);
	RenderMesh2D(meshes["beak"], shaders["VertexColor"], modelMatrix);

	modelMatrix = glm::mat3(1);
	modelMatrix *= Transform2D::Translate(resolution.x * 0.25 + 25 + one, gravity + up + resolution.y / 2 - 10 + one);
	modelMatrix *= Transform2D::Rotate(-1.39626);
	modelMatrix *= angleMatrix;
	modelMatrix *= Transform2D::Scale(2, 2);
	RenderMesh2D(meshes["beak"], shaders["VertexColor"], modelMatrix);

	//EYES
	modelMatrix = glm::mat3(1);
	modelMatrix *= Transform2D::Translate(resolution.x * 0.25 + 70 + one, gravity + up + resolution.y / 2 + one);
	RenderMesh2D(meshes["eyesColor"], shaders["VertexColor"], modelMatrix);

	modelMatrix = glm::mat3(1);
	modelMatrix *= Transform2D::Translate(resolution.x * 0.25 + 65 + one, gravity + up + resolution.y / 2 + one);
	RenderMesh2D(meshes["eyesWhite"], shaders["VertexColor"], modelMatrix);

	//BEAK
	modelMatrix = glm::mat3(1);
	modelMatrix *= Transform2D::Translate(resolution.x * 0.25 + 70 + one, gravity + up + resolution.y / 2 - 8 + one);
	RenderMesh2D(meshes["beak"], shaders["VertexColor"], modelMatrix);

	//HEAD
	head_x = resolution.x * 0.25 + 55;
	head_y = gravity + up + resolution.y / 2;
	modelMatrix = glm::mat3(1);
	modelMatrix *= Transform2D::Translate(resolution.x * 0.25 + 55 + one, gravity + up + resolution.y / 2 + one);
	RenderMesh2D(meshes["circle"], shaders["VertexColor"], modelMatrix);

	//TAIL
	modelMatrix = glm::mat3(1);
	modelMatrix *= Transform2D::Translate(resolution.x * 0.25 - 10 + one, gravity + up + resolution.y / 2 + 10 + one);
	modelMatrix *= angleMatrix;
	//modelMatrix *= Transform2D::Rotate(0.785398);
	modelMatrix *= Transform2D::Scale(2, 2);
	RenderMesh2D(meshes["beak"], shaders["VertexColor"], modelMatrix);

	modelMatrix = glm::mat3(1);
	modelMatrix *= Transform2D::Translate(resolution.x * 0.25 - 10 + one, gravity + up + resolution.y / 2 + 10 + one);
	modelMatrix *= angleMatrix;
	modelMatrix *= Transform2D::Rotate(-0.349066);
	modelMatrix *= Transform2D::Scale(2, 2);
	RenderMesh2D(meshes["beak"], shaders["VertexColor"], modelMatrix);

	modelMatrix = glm::mat3(1);
	modelMatrix *= Transform2D::Translate(resolution.x * 0.25 - 10 + one, gravity + up + resolution.y / 2 + 10 + one);
	modelMatrix *= angleMatrix;
	modelMatrix *= Transform2D::Rotate(0.349066);
	modelMatrix *= Transform2D::Scale(2, 2);
	RenderMesh2D(meshes["beak"], shaders["VertexColor"], modelMatrix);

	//BODY
	modelMatrix = glm::mat3(1);
	modelMatrix *= Transform2D::Translate(resolution.x * 0.25 + 25 + one, gravity + up + resolution.y / 2 + one);
	modelMatrix *= Transform2D::Scale(1.5, 1.5);
	RenderMesh2D(meshes["circle"], shaders["VertexColor"], modelMatrix);

	//LEGS
	modelMatrix = glm::mat3(1);
	modelMatrix *= Transform2D::Translate(resolution.x * 0.25 - 20 + one, gravity + up + resolution.y / 2 - 10 + one);
	modelMatrix *= Transform2D::Rotate(100);
	modelMatrix *= angleMatrix;
	RenderMesh2D(meshes["beak"], shaders["VertexColor"], modelMatrix);

	modelMatrix = glm::mat3(1);
	modelMatrix *= Transform2D::Translate(resolution.x * 0.25 - 20 + one, gravity + up + resolution.y / 2 - 20 + one);
	modelMatrix *= Transform2D::Rotate(100);
	modelMatrix *= angleMatrix;
	RenderMesh2D(meshes["beak"], shaders["VertexColor"], modelMatrix);



	//if (glisUpWall == resolution.y / 2) {
	//	floatDown = FALSE;
	//	floatUp = TRUE;
	//}
	//if (glisUpWall == resolution.y) {
	//	floatDown = TRUE;
	//	floatUp = FALSE;
	//}
	//if (floatDown)
	//	glisUpWall--;
	//if (floatUp)
	//	glisUpWall++;
	////cout << glisUpWall << endl;
	//modelMatrix = glm::mat3(1);
	//modelMatrix *= Transform2D::Translate(resolution.x / 2, glisUpWall);
	//modelMatrix *= Transform2D::Rotate(3.14159265);
	//RenderMesh2D(meshes["brick"], shaders["VertexColor"], modelMatrix);


	if (!LOST) {

		float startLine = resolution.x * 0.2;
		float lastLine = resolution.x * 0.9;
		float backLine = resolution.x;
		lastLine = backLine + backLine * 0.2;

		float upperBrick_x;
		float bottomBrick_x;
		float upperBrick_y = resolution.y;
		float bottomBrick_y = 0;


		for (int i = 0; i < 7; i++) {

			upperBrick_x = lastLine - wallOffsets[i] + betweenOffsets[i] * i;
			bottomBrick_x = lastLine - wallOffsets[i] + betweenOffsets[i] * i;

			if (upperBrick_x < startLine) {
				firstWall = FALSE;
				wallOffsets[i] = 0;
				betweenOffsets[i] = 0;
				if (firstLevel) {
					lower[i] = (rand() % 15 + 5) * 0.1;
					upper[i] = 2 - lower[i];
				}
				else if (secondLevel) {
					lower[i] = (rand() % 16 + 6) * 0.1;
					upper[i] = 2.4 - lower[i];
				}
				else if (thirdLevel) {
					lower[i] = (rand() % 17 + 6) * 0.1;
					upper[i] = 2.6 - lower[i];
				}
				upperBrick_x = lastLine - wallOffsets[i] + betweenOffsets[i] * i;
				bottomBrick_x = lastLine - wallOffsets[i] + betweenOffsets[i] * i;
			}
		
			if (firstWall && i==0) {
				if (glisUpWall == resolution.y) {
					up_FloatDown = TRUE;
					up_FloatUp = FALSE;
				}
				if (glisUpWall == resolution.y / 2) {
					up_FloatDown = FALSE;
					up_FloatUp = TRUE;
				}
				if (up_FloatDown)
					glisUpWall-=0.5;
				if (up_FloatUp)
					glisUpWall+=0.5;
				upperBrick_y = glisUpWall;

				if (glisDownWall == 0) {
					down_FloatUp = TRUE;
					down_FloatDown = FALSE;
				}
				if (glisDownWall == resolution.y / 2) {
					down_FloatDown = TRUE;
					down_FloatUp = FALSE;
				}
				if (down_FloatDown)
					glisDownWall-=0.5;
				if (down_FloatUp)
					glisDownWall+=0.5;
				bottomBrick_y = glisDownWall;

			}else {
				upperBrick_y = resolution.y;
				bottomBrick_y = 0;
			}


			float upDistanceX = upperBrick_x - brickWidth / 2;
			float upDistanceY = upperBrick_y - brickHeight * upper[i];
			float downDistanceX = bottomBrick_x - brickWidth / 2;
			float downDistanceY = brickHeight * lower[i];

			if (upDistanceX - head_x == 0 && (head_y >= upDistanceY)) {
				//a atins peretele de sus
				LOST = TRUE;
				cout << "--------------------------" << endl;
				cout <<"|"<< "SCORE: " << SCORE <<"|"<< endl;
				cout << "--------------------------" << endl;
				SCORE = 0;
			}
			if (downDistanceX - head_x == 0 && (head_y <= downDistanceY)) {
				//a atins peretele de sus
				LOST = TRUE;
				cout << "SCORE: " << SCORE << endl;
				SCORE = 0;
			}
			if (upDistanceX - head_x == 0 ||
				downDistanceX - head_x == 0) {
				SCORE++;
			}
			if (SCORE > 25)
				secondLevel = TRUE;
			else if (SCORE > 45)
				thirdLevel = TRUE;

			modelMatrix = glm::mat3(1);
			modelMatrix *= Transform2D::Translate(upperBrick_x, upperBrick_y);
			modelMatrix *= Transform2D::Scale(1, upper[i]);
			modelMatrix *= Transform2D::Rotate(3.14159265);
			RenderMesh2D(meshes["brick"], shaders["VertexColor"], modelMatrix);
			modelMatrix = glm::mat3(1);
			modelMatrix *= Transform2D::Translate(bottomBrick_x, bottomBrick_y);
			modelMatrix *= Transform2D::Scale(1, lower[i]);
			RenderMesh2D(meshes["brick"], shaders["VertexColor"], modelMatrix);

			wallOffsets[i]++;

			//cout << "PASARE " << head_y << endl;
		}
	}
	if (LOST) {
		for (int i = 0; i < 7; i++) {
				modelMatrix = glm::mat3(1);
				modelMatrix *= Transform2D::Translate(resolution.x * 0.2 * i, gravity + up + resolution.y / 2 * i);
				modelMatrix *= angleMatrix;
				modelMatrix *= Transform2D::Rotate(-0.785398);
				RenderMesh2D(meshes["feather"], shaders["VertexColor"], modelMatrix);

				modelMatrix = glm::mat3(1);
				modelMatrix *= Transform2D::Translate(resolution.x * 0.2 * i, gravity + up + resolution.y / 2 * i);
				modelMatrix *= angleMatrix;
				modelMatrix *= Transform2D::Rotate(-0.785398);
				RenderMesh2D(meshes["feather"], shaders["VertexColor"], modelMatrix);

				modelMatrix = glm::mat3(1);
				modelMatrix *= Transform2D::Translate(resolution.x * 0.2 * i, gravity + up + resolution.y / 2 * i + 50);
				modelMatrix *= angleMatrix;
				modelMatrix *= Transform2D::Rotate(-0.785398);
				RenderMesh2D(meshes["feather"], shaders["VertexColor"], modelMatrix);

				//falling bird
			one++;
			if (one > resolution.y) {
				one = 0;
			}


		}


	}

	// e necesar permanet sa dai render permanent pentru ceva

	//MOON
	modelMatrix = glm::mat3(1);
	modelMatrix *= Transform2D::Translate(resolution.x * 0.5, resolution.y * 0.8);
	modelMatrix *= Transform2D::Scale(10, 10);
	RenderMesh2D(meshes["eyesWhite"], shaders["VertexColor"], modelMatrix);
}

void Tema1::FrameEnd()
{

}

void Tema1::OnInputUpdate(float deltaTime, int mods)
{


}

void Tema1::OnKeyPress(int key, int mods)
{
	// add key press event
	if (key == GLFW_KEY_SPACE) {
		startFlying = TRUE;
		waitStart = FALSE;
	}
}

void Tema1::OnKeyRelease(int key, int mods)
{
	// add key release event
	if (key == GLFW_KEY_SPACE) {
		startFlying = FALSE;
	}

}

void Tema1::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
	// add mouse move event
}

void Tema1::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button press event
}

void Tema1::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button release event
}

void Tema1::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}

void Tema1::OnWindowResize(int width, int height)
{
}
