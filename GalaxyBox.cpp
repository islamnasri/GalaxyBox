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
  srand(time(0));

  // Create game window 
  WindowController gameWindow;

  // Create game world
  b2World world(gravity);

  // Create the contact manager
  //ContactListener* contactManager;
  //contactManager = new ContactListener();
  //world.SetContactListener(contactManager);
  //delete contactManager;

  //Create game world controller
  WorldController gameWorld;

  // Create player controllables
  //PlayerController gamePlayer(world);

  // Initilize neccessaries
  gameWindow.InitWindow();
  gameWorld.InitBorders(world);

  // Create player's ball
  gameWorld.GenerateWorldObjects(world);
  
  

  while(gameWindow.IsRunning())
  {
    gameWindow.Begin();

    // Check User Input

    // Update physics of all objects
    if(gameWorld.UpdateWorld(world))
    {
      //gamePlayer.Update();

      gameWorld.UpdateElements();

      //check contacts
      
    }

    //gameBall.CheckCollision(world);

    // Start rendering window
    gameWindow.Update();

    // Render all objects
    gameWorld.DrawWorld(gameWindow);

    // Show what has been updated in the window.
    gameWindow.End();
  }

  return 0;
}

