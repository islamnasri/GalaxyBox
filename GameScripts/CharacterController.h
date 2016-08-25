
#ifndef CHARACTER_CREATOR_H
#define CHARACTER_CREATOR_H



#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>

using namespace sf;

namespace GalaxyBox
{
	class CharacterController
	{
	 protected:
		RectangleShape rect;
		b2Body* body;
		b2BodyDef bodyDef;
		b2PolygonShape bodyShape;
		b2FixtureDef bodyFixtureDef;

	 public:
	 	// Abstract Attributes
	 	

	 	// Functions
		void MakeRectanglePhysics(Vector2f size, Vector2f& position, b2World& world, float rotation = 0, bool isDynamic = true);
		void MakeRectangleVisual(Vector2f size, Color fillColor, Color outlineColor, float thickness);
		void Update();
		//void MoveTowards(b2Vec2 pos, b2Vec2 nextPos, float lerpRate);
		void Lerp(b2Vec2 nextPos, float lerpRate, bool& done);
		void PushWith(b2Vec2 impulse, b2Vec2 nextPos, bool& keepMoving);
		Shape& GetShape();
	};
}
#endif