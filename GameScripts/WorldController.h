#ifndef GAME_WORLD_H
#define GAME_WORLD_H

#include <Box2D\Box2D.h>
#include <SFML\Graphics.hpp>
#include <iostream>
#include <vector>
#include <array>
#include "Pillar.h"
#include "Ball.h"
#include "CharacterController.h"

using namespace std;

namespace GalaxyBox
{
	class WorldController
	{
		protected:
		     float timeElapsedSinceLastFrame;
		     float borderSize;
		     Pillar topBorder, bottomBorder, leftBorder, rightBorder;
		     

		public:
			// Abstract Variables
			static vector<Ball> OBJECTS_LIST;

			// Functions
			WorldController();
			bool UpdateWorld(b2World& world);
			void InitBorders(b2World& world);
			void GenerateWorldObjects(b2World& world, int noOfSpeedObjects = 1, int noOfKillerObjects = 1);
			void DrawWorld(WindowController& gameWindow);
			void AddElement(Ball& c);
			void UpdateElements();
	};
}

#endif