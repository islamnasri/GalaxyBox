#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include "GameScripts/CharacterCreator.h"
#include "GameScripts/WindowController.h"  
#include <iostream>
#include <sstream>  // for ostringstream
#include <vector>

using namespace std;
using namespace sf;
using namespace GalaxyBox;

// convert all the functions used by "window" to Windowc instances.
// create GameWorld.cpp and transfer the Border making code to it.
// create EventHandler to update player's controls in GameWorld.cpp.
// create the four platforms the player is going to control.
// create the ball that is going to move according to concept.
Font loadFont(const string& fontFilename = "resources/04b03.ttf")
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
  // Timer for fixed update
  float fixedTimeStep = 0.02f; // 50 times per second
  Clock fixedUpdateClock;
  float timeElapsedSinceLastFrame = 0;

  // gameWindow creation
  WindowC gameWindow;
  gameWindow.InitWindow();

  

  // Border creation
  Vector2f horizontalBorderSize(gameWindowSizeX,gameWindowBorderSize);
  Vector2f verticalBorderSize(gameWindowBorderSize,gameWindowSizeY-gameWindowBorderSize*2);
  Vector2f    topBorderPos(gameWindowSizeX/2                 ,gameWindowBorderSize/2);
  Vector2f bottomBorderPos(gameWindowSizeX/2                 ,gameWindowSizeY-gameWindowBorderSize/2);
  Vector2f   leftBorderPos(gameWindowBorderSize/2            ,gameWindowSizeY/2);
  Vector2f  rightBorderPos(gameWindowSizeX-gameWindowBorderSize/2,gameWindowSizeY/2);
  CharacterCreator topBorder;
              topBorder.thickness = -1;
              topBorder.outlineColor = Color::Black;
              topBorder.fillColor = Color(100, 100, 100);
              topBorder.MakeRectangle(world, horizontalBorderSize, topBorderPos, 0.0, false);
CharacterCreator bottomBorder;
              bottomBorder.thickness = -1;
              bottomBorder.outlineColor = Color::Black;
              bottomBorder.fillColor = Color(100, 100, 100);
              bottomBorder.MakeRectangle(world, horizontalBorderSize, bottomBorderPos, 0.0, false);
CharacterCreator leftBorder;
              leftBorder.thickness = -1;
              leftBorder.outlineColor = Color::Black;
              leftBorder.fillColor = Color(100, 100, 100);
              leftBorder.MakeRectangle(world, horizontalBorderSize, leftBorderPos, 0.0, false);
CharacterCreator rightBorder;
              rightBorder.thickness = -1;
              rightBorder.outlineColor = Color::Black;
              rightBorder.fillColor = Color(100, 100, 100);
              rightBorder.MakeRectangle(world, horizontalBorderSize, rightBorderPos, 0.0, false);                                    


  // A vector/list of boxes
  vector<CharacterCreator> boxList;
  Vector2f dynamicBoxSize(32,32);

  // Text creation
  Font font = loadFont();
  Text text;
  text.setFont(font);  
  text.setCharacterSize(16);
  text.setPosition(3, -3);
  text.setFillColor(Color::White);

  // A buffer to check whether left mouse button has been clicked before or not
  bool leftMousePressed = false;

  while(gameWindow.isOpen())
  {
    Event event;
    while (gameWindow.pollEvent(event));
    {
      // This is input handling via poll event
      // Do not use this for game input
      // Why? Delay issues
      // READ SFML DOCUMENTATION!
      if(event.type == Event::Closed)
        gameWindow.close();
    }

    // This is input handling without poll event
    // READ SFML DOCUMENTATION!
    if (Mouse::isButtonPressed(Mouse::Left))
      {
        if(!leftMousePressed)
        {
          Vector2f pos = Vector2f( Mouse::getPosition(gameWindow) );
          CharacterCreator r;
          r.thickness = 1;
          r.outlineColor = Color::Black;
          r.fillColor = Color(100, 100, 100);
          r.MakeRectangle(world, dynamicBoxSize, pos);
          boxList.push_back(r);
          leftMousePressed = true;
        }
      }
    else
    {
      leftMousePressed = false;
    }

    // We get the time elapsed since last frame and add it to timeElapsedSinceLastFrame
    timeElapsedSinceLastFrame += fixedUpdateClock.restart().asSeconds();

    // If sufficient time has elapsed, we update the physics
    if(timeElapsedSinceLastFrame >= fixedTimeStep)
    {
      // Step is used to update physics position/rotation
      world.Step(fixedTimeStep, //update frequency
                    8,                //velocityIterations
                    3                 //positionIterations  
                   );

      // Update the objects that uses physics
         topBorder.update();
      bottomBorder.update();
        leftBorder.update();
       rightBorder.update();

      for(int i = 0; i < boxList.size(); i++)
      {
        boxList[i].update();
      }

      // timeElapsedSinceLastFrame can be higher than fixedTimeStep,
      // so we deduct timeElapsedSinceLastFrame with fixedTimeStep
      timeElapsedSinceLastFrame -= fixedTimeStep;
    }

    // Rendering
    //gameWindow.clear(Color(100, 149, 237)); // CORNFLOWER BLUE!

    // Render all objects
    gameWindow.Draw(   topBorder.getShape());
    gameWindow.Draw(bottomBorder.getShape());
    gameWindow.Draw(  leftBorder.getShape());
    gameWindow.Draw( rightBorder.getShape());
    
    for(int i = 0; i < boxList.size(); i++)
    {
      gameWindow.Draw(boxList[i].getShape());
    }

    ostringstream boxListStream;
    boxListStream << boxList.size();
    text.setString("Number of boxes: "+boxListStream.str());
    gameWindow.Draw(text);

    gameWindow.Update();
  }

  return 0;
}
