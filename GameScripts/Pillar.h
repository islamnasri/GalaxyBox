

#ifndef PILLAR_H
#define PILLAR_H

#include <SFMl\Graphics.hpp>
#include <vector>
#include <Box2D\Box2D.h>
#include "CharacterController.h"

namespace GalaxyBox
{
	class Pillar : public CharacterController
	{
		protected:
  			Vector2f size;


		public:
			// Abstract Variables
  			Vector2f pos;
  			b2Vec2 nextPos;
  			b2Vec2 velocity;
			bool move = false;
			bool moveFromCenter = true;
			float timer = 0;

			// Functions
			Pillar();
			Pillar(Vector2f size, Vector2f position);
			void CreatePillar(b2World& world, bool dynamic = false);

	};
}

#endif