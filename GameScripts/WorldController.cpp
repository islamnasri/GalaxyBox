#include <SFML\Graphics.hpp>
#include <Box2D\Box2D.h>
#include "WorldController.h"

#include "Square.h"
#include <vector>
#include <ctime>
#include <string>
#include <sstream>  // for ostringstream


using namespace std;
using namespace sf;
using namespace TimeBox;

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


	//text = Text("saddddd", GLOBAL_FONT, 20);
  	//text.setStyle(Text::Bold);
  	//text.setFillColor(Color::Green);
  	//text.setPosition(SCREEN_CENTER_X, SCREEN_CENTER_Y);
  	//text.setOrigin(SCREEN_CENTER_X / 2, SCREEN_CENTER_Y / 2);
}

bool WorldController::UpdateWorld(b2World& world)
{
	// We get the time elapsed since last frame and add it to timeElapsedSinceLastFrame
	timeElapsedSinceLastFrame += 0.1f;
	buttonPressTimer += 1;

	// If sufficient time has elapsed, we update the physics
	if (buttonPressTimer > 10 && Keyboard::isKeyPressed(Keyboard::Space))
	{
		slowMo = (slowMo)? false : true;

		if (slowMo)
		{
			FIXED_TIME_STEP = slowMoTime;
			slowMoTimer = 200;
		}
		else
		{
			FIXED_TIME_STEP = regularTime;
		}

		buttonPressTimer = 0;
	}

	if (slowMo == true && slowMoTimer > 0)
	{
		slowMoTimer -= 1;
		if (slowMoTimer == 0)
		{
			FIXED_TIME_STEP = regularTime;
			slowMo = false;
		}
	}


    if(timeElapsedSinceLastFrame >= FIXED_TIME_STEP)
    {
		// Step is used to update physics position/rotation
		//update frequency
		//velocityIterations
	    //positionIterations

	    world.Step(FIXED_TIME_STEP, WORLD_VELOCITY_RATE, WORLD_POSITION_RATE);

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
	
	
	for (int i = 0; i < platformList.size(); i++)
      platformList[i].DrawShape(gameWindow);

	topBorder.DrawShape(gameWindow);
    bottomBorder.DrawShape(gameWindow);
    leftBorder.DrawShape(gameWindow);
    rightBorder.DrawShape(gameWindow);
}

void WorldController::GeneratePlatforms(b2World& world)
{
	platformSpawnTimer += 1;

	if (platformSpawnTimer > 275)
	{
		Vector2f size((rand() % 100) + 200, 20);
		Vector2f pos( (rand() % WINDOW_SIZE_X - size.x) + size.x , -20);
		
		Square platform(0, size, pos, ((int)size.x % 2 == 0)? AgeUp : AgeDown, world, true);

  		//ball.velocity.Set( (rand() % 5) - 2, (rand() % 5) - 2);

  		platformList.push_back(platform);

  		for (int i = 0; i < noOfPlatforms; i++)
  		{
  			Vector2f size(40, 40);
			Vector2f pos( (rand() % SCREEN_CENTER_X - 250) + SCREEN_CENTER_X + 100, (rand() % 100) - 300);
			
			Square platform(0, size, pos, ((int)size.x % 2 == 0)? AgeUp : AgeDown, world, true);

	  		platformList.push_back(platform);
  		}


  		platformSpawnTimer = 0;
	}

}

void WorldController::UpdateElements(RenderWindow& window)
{
	for (int i = 0; i < platformList.size(); i++)
		if (platformList[i].TimeToDie())
			platformList.erase( platformList.begin() + i);

	for (int i = 0; i < platformList.size(); i++)
          platformList[i].Update(window);
}

void WorldController::CheckPlatformType()
{
	for (int i = 0; i < platformList.size(); i++)
          platformList[i].UpdatePlatform();	
}
