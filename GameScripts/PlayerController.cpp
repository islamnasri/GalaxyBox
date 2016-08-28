#include <SFML\Window.hpp>
#include <Box2D\Box2D.h>
#include <vector>
#include "PlayerController.h"
#include "GalaxyBox.h"
#include <iostream>
#include <thread>

using namespace std;
using namespace GalaxyBox;

PlayerController::PlayerController(b2World& world)
{
	Vector2f size(WINDOW_SIZE_X/2, borderSize);

	TBlock = Pillar(size, Vector2f( SCREEN_CENTER_X , SCREEN_CENTER_Y/2));
	TBlock.CreatePillar(world);

	BBlock = Pillar(size, Vector2f( SCREEN_CENTER_X , WINDOW_SIZE_Y - SCREEN_CENTER_Y/2));
    BBlock.CreatePillar(world);

    size = Vector2f(borderSize , WINDOW_SIZE_Y/2);

	LBlock = Pillar(size, Vector2f( SCREEN_CENTER_X/2 , SCREEN_CENTER_Y));
    LBlock.CreatePillar(world);

	RBlock = Pillar(size, Vector2f( WINDOW_SIZE_X - SCREEN_CENTER_X/2 , SCREEN_CENTER_Y ));
    RBlock.CreatePillar(world);
}

void PlayerController::DrawBlocks(WindowController& gameWindow)
{
	gameWindow.Draw(TBlock.GetRectangle());
    gameWindow.Draw(BBlock.GetRectangle());
    gameWindow.Draw(LBlock.GetRectangle());
    gameWindow.Draw(RBlock.GetRectangle());
}

void PlayerController::Update()
{
	ControlBlock(TBlock, "up");
	ControlBlock(BBlock, "down");
	ControlBlock(LBlock, "left");
	ControlBlock(RBlock, "right");


	TBlock.Update();
	BBlock.Update();
	LBlock.Update();
	RBlock.Update();
}

void PlayerController::ControlBlock(Pillar& block, string direction)
{
	string inDirection = "";
	block.timer += FIXED_TIME_STEP;

	if (block.timer >= timeToUpdateBlock)
	{
		if (Keyboard::isKeyPressed(Keyboard::Right) && direction == "right")
			inDirection = "right";
		else if (Keyboard::isKeyPressed(Keyboard::Left) && direction == "left")
			inDirection = "left";
		else if (Keyboard::isKeyPressed(Keyboard::Up) && direction == "up")
			inDirection = "up";
		else if (Keyboard::isKeyPressed(Keyboard::Down) && direction == "down")
			inDirection = "down";

		if (inDirection != "")
		{
			if (block.moveFromCenter)
			{
				if (inDirection == "right")
					block.nextPos.Set(block.pos.x + distanceFromCenter, block.pos.y);
				if (inDirection == "left")
					block.nextPos.Set(block.pos.x - distanceFromCenter, block.pos.y);
				if (inDirection == "up")
					block.nextPos.Set(block.pos.x, block.pos.y - distanceFromCenter/2);
				if (inDirection == "down")
					block.nextPos.Set(block.pos.x, block.pos.y + distanceFromCenter/2);
			}
			else
				block.nextPos.Set(block.pos.x, block.pos.y);

			block.moveFromCenter = (block.moveFromCenter)? false : true;
			block.move = true;
			block.timer = 0;
		}
	}

	if (block.move)
		block.Lerp(block.nextPos, lerpSpeed, block.move);
}