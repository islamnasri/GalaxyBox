

#ifndef Square_H
#define Square_H

#include <SFMl\Graphics.hpp>
#include <vector>
#include <string>
#include <Box2D\Box2D.h>


#include "GameConstants.h"
#include "WindowController.h"
#include "CharacterController.h"


using namespace std;

namespace TimeBox
{
	class Square : public CharacterController
	{
		protected:
			// Abstract Variables
  			Texture* tex;
  			float changeTypeTimer = 0;
  			float changeTypeMaxTimer;
  			int ageCounter = 0;


  			// Functions
			void MoveWithConstantSpeed();

		public:
			// Abstract Variables
			Vector2i mouseClickPos;
			Vector2f distanceToTravel;
			int age = 5;
			int followUpAge = age;

			// State Machines
			bool isPlatform;
			bool startCountingMouseDistance = false;
			bool isSpeedConstant = false;
			bool alive = false;

			// Functions
			Square();
			~Square();
			Square(int imageNo, Vector2f size, Vector2f pos, OBJECT_TYPES type, b2World& world, bool isPlatform = false);
			void MakeSquareVisual(Vector2f size, int imageNo);
			void MakeSquareVisual(Vector2f size, Color fillColor, Color outlineColor, float thickness);
			void Update(RenderWindow& window);
			void CheckCollision(b2World& world);
			void UpdatePlatform();
			bool TimeToDie();
			void Restart();
	};
}

#endif