#include <iostream>
#include <sstream>  // for ostringstream
#include <vector>
#include <array>
#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include <list>
#include <cstdlib>

#include "GameScripts/GalaxyBox.h"


using namespace std;
using namespace sf;
using namespace GalaxyBox;


// create the ball that is going to move according to concept.

int main()
{
  srand(time(NULL));

  // Create game window 
  WindowController gameWindow;

  // Create game world
  b2World world(gravity);

  //Create game world controller
  WorldController gameWorld;

  // Create player controllables
  PlayerController gamePlayer(world);

  // Create sprites controller
  Ball gameObjects;

  // Initilize neccessary
  gameWindow.InitWindow();
  gameWorld.InitBorders(world);

  // Create player's ball
  Vector2f pos(SCREEN_CENTER_X, SCREEN_CENTER_Y);
  Vector2f ballSize(25,25);
  Ball gameBall(0, ballSize, pos, 25, Player,world);
  gameBall.velocity.Set( (rand() % 20) - 10, (rand() % 20) - 10);

  Ball rBall(0, ballSize, pos, 25, SpeedBooster,world);
  rBall.velocity.Set( (rand() % 40) - 10, (rand() % 25) - 5);

  while(gameWindow.IsRunning())
  {

    gameWindow.Begin();

    // Check User Input

    // Update physics of all objects
    if(gameWorld.UpdateWorld(world))
    {
      gamePlayer.Update();

      gameBall.CheckCollision();
      gameBall.Update(true);

      rBall.Update();

    }
    // Start rendering window
    gameWindow.Update();

    // Render all objects
    gameWorld.DrawBorders(gameWindow);
    gamePlayer.DrawBlocks(gameWindow);
    gameBall.DrawBall(gameWindow);
    rBall.DrawBall(gameWindow);



    // Show what has been updated in the window.
    gameWindow.End();
  }

  return 0;
}
