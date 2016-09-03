
#ifndef WINDOW_CONTROLLER_H
#define WINDOW_CONTROLLER_H


#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>

using namespace std;
using namespace sf;

namespace GalaxyBox
{
    class WindowController
    {
      protected:
      	RenderWindow GameWindow;
        Texture* backgroundTex;
        RectangleShape bg;

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