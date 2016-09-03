

#ifndef GAME_BALL_H
#define GAME_BALL_H

#include <SFMl\Graphics.hpp>
#include <vector>
#include <string>
#include <Box2D\Box2D.h>


#include "GameConstants.h"
#include "WindowController.h"
#include "CharacterController.h"
#include "ContactListener.h"

using namespace std;

namespace GalaxyBox
{
	class Ball : public CharacterController
	{
		protected:
			// Abstract Variables
  			Texture* tex;

  			// Functions
			void MoveWithConstantSpeed();

		public:
			// Abstract Variables
			bool isSpeedConstant = false;

			// Functions
			Ball();
			~Ball();
			Ball(int imageNo, Vector2f size, Vector2f pos, float radius, string type,b2World& world);
			void MakeCircleVisual(Vector2f size, int imageNo, float radius);
			void Update();
			void CheckCollision();
			void DrawBall(WindowController& gameWindow);
	};
}

#endif