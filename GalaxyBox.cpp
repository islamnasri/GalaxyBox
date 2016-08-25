#include <iostream>
#include <sstream>  // for ostringstream
#include <vector>
#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include "GameScripts/GalaxyBox.h"


using namespace std;
using namespace sf;
using namespace GalaxyBox;

// create WorldController.cpp and transfer the Border making code to it.
// create the four platforms the player is going to control.
// create the ball that is going to move according to concept.


Font loadFont(const string& fontFilename = "Resources/04b03.ttf")
{
   Font myFont;
   if (!myFont.loadFromFile(fontFilename))
   {
      cout << "Can not load font from " << fontFilename << endl;
      exit(1);
   }
   return myFont;
}

int main()
{
  // Create game window 
  WindowController gameWindow;

  // Create game world
  b2World world(gravity);

  //Create game world controller
  WorldController gameWorld;

  // Create player controllables
  PlayerController gamePlayer(world);

  // Initilize neccessary
  gameWindow.InitWindow();
  gameWorld.InitBorders(world);


  // A vector/list of boxes
  vector<CharacterController> boxList;
  Vector2f dynamicBoxSize(32,32);

  // A buffer to check whether left mouse button has been clicked before or not
  bool leftMousePressed = false;

  while(gameWindow.IsRunning())
  {

    gameWindow.Begin();

    // Check User Input
    
    if (Mouse::isButtonPressed(Mouse::Left))
      {
        if(!leftMousePressed)
        {
          Vector2f pos = Vector2f( Mouse::getPosition(gameWindow.Get()) );
          CharacterController r;
          r.MakeRectanglePhysics(dynamicBoxSize, pos, world);
          r.MakeRectangleVisual(dynamicBoxSize, Color::White, Color::Black, 1);

          boxList.push_back(r);
          leftMousePressed = true;
        }
      }
    else
    {
      leftMousePressed = false;
    }
    


    // Update physics of all objects
    if(gameWorld.UpdateWorld(world))
    {
      
      gamePlayer.Update();

      
      for(int i = 0; i < boxList.size(); i++)
      {
        boxList[i].Update();
      }

    }

    // Start rendering window
    gameWindow.Update();

    // Render all objects
    gameWorld.DrawBorders(gameWindow);
    gamePlayer.DrawBlocks(gameWindow);
    
    for(int i = 0; i < boxList.size(); i++)
    {
      gameWindow.Draw(boxList[i].GetShape());
    }

    // Show what has been updated in the window.
    gameWindow.End();
  }

  return 0;
}
