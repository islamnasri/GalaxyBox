

#ifndef SPRITE_CONTROLLER_H
#define SPRITE_CONTROLLER_H

#include <SFMl\Graphics.hpp>
#include <vector>
#include <string>
#include <Box2D\Box2D.h>
#include "GalaxyBox.h"
#include "CharacterController.h"

using namespace std;

namespace GalaxyBox
{
	class Ball : public CharacterController
	{
		protected:
			// Abstract Variables
  			Texture* tex;

			void ApplyVelocity(b2Vec2 velo);
			void MoveWithConstantSpeed();
		public:
			// Abstract Variables


			// Functions
			Ball();
			Ball(int imageNo, Vector2f size, Vector2f pos, float radius, OBJECT_TYPES type,b2World& world);
			void MakeCircleVisual(Vector2f size, int imageNo, float radius);
			void Update(bool isSpeedConstant = false);
			void CheckCollision();
			void DrawBall(WindowController& gameWindow);
	};
}

#endif