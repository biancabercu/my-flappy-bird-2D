#pragma once

#include <Component/SimpleScene.h>
#include <string>
#include <Core/Engine.h>

class Tema1 : public SimpleScene
{
public:
	Tema1();
	~Tema1();

	void Init() override;

private:
	void FrameStart() override;
	void Update(float deltaTimeSeconds) override;
	void FrameEnd() override;

	void OnInputUpdate(float deltaTime, int mods) override;
	void OnKeyPress(int key, int mods) override;
	void OnKeyRelease(int key, int mods) override;
	void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
	void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
	void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
	void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
	void OnWindowResize(int width, int height) override;

protected:
	glm::mat3 modelMatrix;
	glm::mat3 angleMatrix;
	glm::mat3 staticMatrix;
	float translateX, translateY;
	float scaleX, scaleY;
	float angularStep;
	int random[7];
	float upper[7];
	float lower[7];
	int wallOffsets[7];
	int betweenOffsets[7];
	int up = 0;
	int pressedKey;
	float gravity;
	bool startFlying = FALSE, waitStart = TRUE;
	int one;
	float head_x, head_y;
	float brickWidth;
	float brickHeight;
	bool LOST = FALSE;
	int SCORE;
	bool firstLevel, secondLevel = FALSE, thirdLevel = FALSE;
	bool firstWall = TRUE;
	bool upBack = FALSE;
	float glisUpWall;
	float glisDownWall;
	bool up_FloatUp, up_FloatDown, down_FloatUp, down_FloatDown;

};
