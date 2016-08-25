#ifndef GAME_WORLD_H
#define GAME_WORLD_H

#include <Box2D\Box2D.h>
#include <SFML\Graphics.hpp>
#include <iostream>
#include <sstream>  // for ostringstream
#include <vector>
#include "GameConstants.h"
#include "WindowController.h"
#include "Pillar.h"

namespace GalaxyBox
{
	class WorldController
	{
		protected:
		     float timeElapsedSinceLastFrame;
		     float borderSize;
		     Pillar topBorder, bottomBorder, leftBorder, rightBorder;

		public:
			WorldController();
			bool UpdateWorld(b2World& world);
			void InitBorders(b2World& world);
			void DrawBorders(WindowController& gameWindow);
	};
}

#endif