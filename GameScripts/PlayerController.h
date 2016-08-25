
#ifndef PLAYER_CONTROLLER_H
#define PLAYER_CONTROLLER_H

#include <SFML\Window.hpp>
#include "Box2D\Box2D.h"
#include "GalaxyBox.h"


namespace GalaxyBox
{
	class PlayerController
	{
		protected:
			float borderSize = 8;
			float distanceFromCenter = 5;
			float timeToUpdateBlock = 2;
			float lerpSpeed = 0.2f;
			Pillar RBlock, LBlock, TBlock, BBlock;

		public:
			PlayerController(b2World& world);
			void DrawBlocks(WindowController& gameWindow);
			void Update();
			void ControlRBlock();
	};
}

#endif