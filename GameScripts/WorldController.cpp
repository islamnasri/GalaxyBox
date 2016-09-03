#include <SFML\Graphics.hpp>
#include <Box2D\Box2D.h>
#include "WorldController.h"
#include "Ball.h"
#include "ContactListener.h"
#include <vector>
#include <ctime>

using namespace std;
using namespace sf;
using namespace GalaxyBox;

vector<Ball> WorldController::OBJECTS_LIST;


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
	    world.Step(FIXED_TIME_STEP, 8, 2);

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

void WorldController::DrawWorld(WindowController& gameWindow)
{
	for (int i = 0; i < OBJECTS_LIST.size(); i++)
      OBJECTS_LIST[i].DrawShape(gameWindow);

	topBorder.DrawShape(gameWindow);
    bottomBorder.DrawShape(gameWindow);
    leftBorder.DrawShape(gameWindow);
    rightBorder.DrawShape(gameWindow);
}

void WorldController::GenerateWorldObjects(b2World& world, int noOfSpeedObjects, int noOfKillerObjects)
{
	//srand(time(NULL));
	Vector2f pos(SCREEN_CENTER_X, SCREEN_CENTER_Y);
	Vector2f ballSize(25,25);

	Ball gameBall(0, ballSize, pos, 25, TYPE[Player], world);
	gameBall.velocity.Set( (rand() % 10) - 5, (rand() % 20) - 10);
	gameBall.isSpeedConstant = true;

	OBJECTS_LIST.push_back(gameBall);

	pos = Vector2f(SCREEN_CENTER_X - 200, SCREEN_CENTER_Y);
  	ballSize = Vector2f(25,25);

  	for (int i = 0; i < noOfSpeedObjects; i++)
	{
		Ball ball(2, ballSize, pos, ballSize.x, TYPE[SpeedBooster],world);
		ball.velocity.Set( (rand() % 5) - 2, (rand() % 5) - 2);
		ball.ApplyVelocity(ball.velocity);

		OBJECTS_LIST.push_back(ball);
	}

	pos = Vector2f(SCREEN_CENTER_X, 100);
	ballSize = Vector2f(20,20);

	for (int i = 0; i < noOfKillerObjects; i++)
	{
		Ball ball(4, ballSize, pos, ballSize.x, TYPE[Killer],world);
  		ball.velocity.Set( (rand() % 5) - 2, (rand() % 5) - 2);

  		OBJECTS_LIST.push_back(ball);

	}

}

void WorldController::AddElement(Ball& c)
{
  	OBJECTS_LIST.push_back(c);
}

void WorldController::UpdateElements()
{
	for (int i = 0; i < OBJECTS_LIST.size(); i++)
          OBJECTS_LIST[i].Update();
}
