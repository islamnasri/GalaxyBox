
#ifndef CHARACTER_CREATOR_H
#define CHARACTER_CREATOR_H



#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include <string>

using namespace std;
using namespace sf;

namespace GalaxyBox
{
	class CharacterController
	{
	 protected:
		RectangleShape rect;
		CircleShape circle;
		b2BodyDef bodyDef;
		b2PolygonShape bodyShapeRectangle;
		b2CircleShape bodyShapeCircle;
		b2FixtureDef bodyFixtureDef;
  		Vector2f size;

	 public:
	 	// Abstract Attributes
		b2Body* body;
	 	Vector2f pos;
  		b2Vec2 velocity;
  		int type;

	 	// Functions
		void MakeShapePhysics(Vector2f size, Vector2f& position, b2World& world, float rotation = 0, bool isDynamic = true, bool isRectangle = true, float radius = 0);
		void Update();
		void Lerp(b2Vec2 nextPos, float lerpRate, bool& done);
		Shape& GetRectangle();
		Shape& GetCircle();
	};
}
#endif