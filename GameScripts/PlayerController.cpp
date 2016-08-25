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
    RBlock.CreatePillar(world, true);
    RBlock.velocity.Set(2,0);
}

void PlayerController::DrawBlocks(WindowController& gameWindow)
{
	gameWindow.Draw(TBlock.GetShape());
    gameWindow.Draw(BBlock.GetShape());
    gameWindow.Draw(LBlock.GetShape());
    gameWindow.Draw(RBlock.GetShape());
}

void PlayerController::Update()
{
	ControlRBlock();


	TBlock.Update();
	BBlock.Update();
	LBlock.Update();
	RBlock.Update();
}

void PlayerController::ControlRBlock()
{
	RBlock.timer += FIXED_TIME_STEP;

	if (Keyboard::isKeyPressed(Keyboard::Right))
	{
		if (RBlock.timer >= timeToUpdateBlock)
		{
			if (RBlock.moveFromCenter)
				RBlock.nextPos.Set(RBlock.pos.x + distanceFromCenter,RBlock.pos.y);
			else
				RBlock.nextPos.Set(RBlock.pos.x, RBlock.pos.y);

			RBlock.moveFromCenter = (RBlock.moveFromCenter)? false : true;
			RBlock.move = true;
			RBlock.timer = 0;
		}
	}

	if (RBlock.move)
		RBlock.Lerp(RBlock.nextPos, lerpSpeed, RBlock.move);
}