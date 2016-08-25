
#ifndef WINDOW_CONTROLLER_H
#define WINDOW_CONTROLLER_H


#include <iostream>
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

namespace GalaxyBox
{
  class WindowController
  {
  protected:
  	RenderWindow GameWindow;

  public:
    void InitWindow();
    void Draw(const Drawable &obj);
    void Begin();
    bool IsRunning();
    void Update();
    void End();
    RenderWindow& Get();
  };
}

#endif