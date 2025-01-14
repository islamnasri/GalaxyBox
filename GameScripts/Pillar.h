

#ifndef PILLAR_H
#define PILLAR_H

#include <SFMl\Graphics.hpp>
#include <vector>
#include <Box2D\Box2D.h>
#include "CharacterController.h"

namespace TimeBox
{
	class Pillar : public CharacterController
	{
		protected:

		public:
			// Abstract Variables
			bool move = false;
			bool moveFromCenter = true;
			float timer = 0;
			b2Vec2 nextPos;

			// Functions
			Pillar();
			Pillar(Vector2f size, Vector2f position);
			void Update();
			void CreatePillar(b2World& world, bool dynamic = false);
			void MakeRectangleVisual(Vector2f size, Color fillColor, Color outlineColor, float thickness);

	};
}

#endif