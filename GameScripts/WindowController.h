
#ifndef WINDOW_CONTROLLER_H
#define WINDOW_CONTROLLER_H


#include <iostream>

using namespace std;

namespace GalaxyBox
{
  class WindowC
  {
  protected:
  	RenderWindow GameWindow;
  	const int windowSizeX = 800, windowSizeY = 600;
   	const int windowBorderSize = 16;

  public:
    void InitWindow();
    void Draw(const Drawable &obj);
    void Update();
  };
}
#endif