#ifndef GAME_WORLD_H
#define GAME_WORLD_H

#include <Box2D\Box2D.h>
#include <SFML\Graphics.hpp>
#include <iostream>
#include <vector>
#include <array>
#include "Pillar.h"
#include "Square.h"
#include "CharacterController.h"

using namespace std;

namespace TimeBox
{
	class WorldController
	{
		protected:
		     float timeElapsedSinceLastFrame;
		     float borderSize;
		     Pillar topBorder, bottomBorder, leftBorder, rightBorder;
		     float slowMoTime = FIXED_TIME_STEP - 0.01f;
		     float regularTime = FIXED_TIME_STEP;
		     float timeStepRate = 0.01f;
		     float buttonPressTimer = 0;
		     float platformSpawnTimer = 1000;
		     int const noOfPlatforms = 5;
  			 Text text;


		public:
			// Abstract Variables
			vector<Square> platformList;
  			int slowMoTimer = 200;

		     // Machine States
		     bool slowMo = false;
		     
			// Functions
			WorldController();
			bool UpdateWorld(b2World& world);
			void InitBorders(b2World& world);
			void GeneratePlatforms(b2World& world);
			void DrawWorld(WindowController& gameWindow);
			void UpdateElements(RenderWindow& window);
			void CheckPlatformType();
	};
}

#endif