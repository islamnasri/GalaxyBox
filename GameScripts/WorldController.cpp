#include <SFML\Graphics.hpp>
#include <Box2D\Box2D.h>
#include "GameConstants.h"
#include "WorldController.h"
#include "WindowController.h"
#include "Pillar.h"

using namespace sf;
using namespace GalaxyBox;


WorldController::WorldController() 
{
	borderSize = 16;
	timeElapsedSinceLastFrame = 0;
}


void WorldController::InitBorders(b2World& world)
{
	Vector2f size(WINDOW_SIZE_X, borderSize);

	topBorder = Pillar(size, Vector2f(SCREEN_CENTER_X , size.y/2));
	topBorder.CreatePillar(world);

	bottomBorder = Pillar(size, Vector2f( SCREEN_CENTER_X , WINDOW_SIZE_Y - size.y/2));
    bottomBorder.CreatePillar(world);
         
    size = Vector2f(borderSize, WINDOW_SIZE_Y);
    
	leftBorder = Pillar(size, Vector2f(size.x/2, SCREEN_CENTER_Y));
    leftBorder.CreatePillar(world);

	rightBorder = Pillar(size, Vector2f(WINDOW_SIZE_X - size.x/2, SCREEN_CENTER_Y));
    rightBorder.CreatePillar(world);
}

bool WorldController::UpdateWorld(b2World& world)
{
	// We get the time elapsed since last frame and add it to timeElapsedSinceLastFrame
	timeElapsedSinceLastFrame += 0.1f;

	// If sufficient time has elapsed, we update the physics
    if(timeElapsedSinceLastFrame >= FIXED_TIME_STEP)
    {
		// Step is used to update physics position/rotation
		//update frequency
		//velocityIterations
	    //positionIterations
	    world.Step(FIXED_TIME_STEP, 8, 3);

	    // Update borders
		topBorder.Update();
		bottomBorder.Update();
		leftBorder.Update();
		rightBorder.Update();

	    // timeElapsedSinceLastFrame can be higher than fixedTimeStep,
	    timeElapsedSinceLastFrame = 0;
      return true;
    }

    return false;
}

void WorldController::DrawBorders(WindowController& gameWindow)
{
	gameWindow.Draw(   topBorder.GetRectangle());
    gameWindow.Draw(bottomBorder.GetRectangle());
    gameWindow.Draw(  leftBorder.GetRectangle());
    gameWindow.Draw( rightBorder.GetRectangle());
}
