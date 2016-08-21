#include <iostream>
#include <iomanip>
#include <SFML/Graphics.hpp>
#include "WindowController.h"

using namespace std;
using namespace sf;
using namespace GalaxyBox;

void WindowC::InitWindow()
{
   // Window creation
   GameWindow.create(VideoMode(windowSizeX, windowSizeY), "SFML with Box2D");

  // Set vSync to true (and as a result, we have a cap of 60FPS)
  GameWindow.setVerticalSyncEnabled(true);
  GameWindow.setActive();

  // Rendering
  GameWindow.clear(Color(100, 149, 237)); // CORNFLOWER BLUE!

  // Create gravity and world, then assign gravity to world
  b2Vec2 gravity(0.f, 9.81f);
  b2World world(gravity);
}

void WindowC::Draw(const Drawable &obj)
{
  GameWindow.draw(obj);
}

void WindowC::Update()
{
    GameWindow.display();
}