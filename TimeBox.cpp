#include <iostream>
#include <sstream>  // for ostringstream
#include <vector>
#include <array>
#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include <list>
#include <cstdlib>

#include "TimeBox.h"


using namespace std;
using namespace sf;
using namespace TimeBox;


// create the ball that is going to move according to concept.
int main()
{
  srand(time(0));
  GLOBAL_FONT.loadFromFile(RESOURCES_FONTS[0]);

  // Create game window 
  WindowController gameWindow;

  // Create game world
  b2World world(gravity);

  //Create game world controller
  WorldController gameWorld;

  // Create player controllables
  //PlayerController gamePlayer(world);

  // Initilize neccessaries
  //GLOBAL_FONT = new Font();
  gameWindow.InitWindow();
  gameWorld.InitBorders(world);


  // Create player
  Vector2f size(25, 25);
  Vector2f pos(SCREEN_CENTER_X , SCREEN_CENTER_Y);

  Square square(0, size, pos, Player, world);

  gameWorld.GeneratePlatforms(world);

  Text text("", GLOBAL_FONT, 20);
  text.setStyle(Text::Bold);
  text.setFillColor(Color::White);
  //text.setOutlineColor(Color::Black);
  text.setPosition(SCREEN_CENTER_X - 200, SCREEN_CENTER_Y - 100);
  text.setOrigin((SCREEN_CENTER_X - 200 ) / 2,(SCREEN_CENTER_Y - 100) / 2);
  text.setString
  ("Game Theme :: Time \n \n" 
    "Game Goal :: Keep The Ball's Age Between 0 & 10 \n \n" 
    "Game Elements :: Red Platform > -1 Of Age \n" 
    "Game Elements :: White Platform > +1 To Age \n" 
    "Game Elements :: Walls > -2 Of Age \n \n"
    "Game Controls :: Left Mouse Button(Ball Speed) <> Space Bar (Slow Time) \n \n"
    "Press Space To Start ...");



  while(gameWindow.IsRunning())
  {
    gameWindow.Begin();

    if (square.alive)
    {


      // Check User Input

      // Update physics of all objects
      if(gameWorld.UpdateWorld(world))
      {
        //gamePlayer.Update();

        square.CheckCollision(world);
        square.Update(gameWindow.Get());

        gameWorld.UpdateElements(gameWindow.Get());
        gameWorld.GeneratePlatforms(world);
        gameWorld.CheckPlatformType();
        
      }


      // Start rendering window
      gameWindow.Update();

      // Render all objects
      gameWorld.DrawWorld(gameWindow);
      square.DrawShape(gameWindow);

      ostringstream streamString;
      streamString << square.age;
      text.setString("Age :: " + streamString.str());

      if (gameWorld.slowMo)
      {
        ostringstream streamString;
        streamString << gameWorld.slowMoTimer;

        text.setString(text.getString() + " :: " + streamString.str() + " :: ");
      }

      if (!square.alive)
      {
        text.setPosition(SCREEN_CENTER_X, SCREEN_CENTER_Y);
        text.setOrigin(SCREEN_CENTER_X / 2,SCREEN_CENTER_Y / 2);
        text.setString("You Died !!! \n \n Press Space To Restart !! \n \n Press  Esc To Exit");
      }

      gameWindow.Get().draw(text);
    }
    else
    {
      // Restart game;
      if (Keyboard::isKeyPressed(Keyboard::Space))
      {
        text.setPosition(18, 20);
        text.setOrigin(9, 10);
        text.setFillColor(Color::Green);

        square.Restart();
        square.alive = true;
      }
      else if (Keyboard::isKeyPressed(Keyboard::Escape))
        gameWindow.Get().close();

      gameWindow.Update();

      gameWindow.Get().draw(text);
    }

    // Show what has been updated in the window.
    gameWindow.End();
  }

  return 0;
}

