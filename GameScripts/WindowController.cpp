#include <iostream>
#include <iomanip>
#include <SFML/Graphics.hpp>
#include "WindowController.h"
#include "GameConstants.h"

using namespace std;
using namespace sf;
using namespace TimeBox;

void WindowController::InitWindow()
{
   // Window creation
   GameWindow.create(VideoMode(WINDOW_SIZE_X, WINDOW_SIZE_Y), "Time Box");

  // Set vSync to true (and as a result, we have a cap of 60FPS)
  GameWindow.setVerticalSyncEnabled(true);
  GameWindow.setActive();

  // Rendering
  GameWindow.clear(Color(100, 149, 237)); // CORNFLOWER BLUE!

  GameWindow.setPosition(Vector2i(50,50));
  
  //backgroundTex = new Texture();
  //backgroundTex->loadFromFile(RESOURCES_IMAGES[1]);
  //bg = RectangleShape();
  //bg.setTexture(backgroundTex);
  //bg.setSize(Vector2f(100,100));
  //bg.setTextureRect(IntRect(0,0,100,100));
  //bg.setPosition(0,0);
}

void WindowController::Draw(const Drawable &obj)
{
  GameWindow.draw(obj);
}


bool WindowController::IsRunning()
{
  return GameWindow.isOpen();
}

void WindowController::Begin()
{
    Event event;
    while (GameWindow.pollEvent(event));
    {
      // This is input handling via poll event
      // Do not use this for game input
      // Why? Delay issues
      // READ SFML DOCUMENTATION!
        if(event.type == Event::Closed)
        {
          //GameWindow.close();
          //cout << "Closing Window" << endl;
          //system("pause");
        }
    }  
}

void WindowController::Update()
{
    // Rendering
    GameWindow.clear(Color::Black); // CORNFLOWER BLUE!
}

void WindowController::End()
{
    //GameWindow.draw(bg);
    GameWindow.display();
}

RenderWindow& WindowController::Get()
{
  return GameWindow;
}