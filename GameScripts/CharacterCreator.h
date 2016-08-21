
#ifndef CHARACTER_CREATOR_H
#define CHARACTER_CREATOR_H



#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>

using namespace sf;

namespace GalaxyBox
{
	class CharacterCreator
	{
	 protected:
		RectangleShape rect;
		b2Body* body;
		b2BodyDef bodyDef;
		b2PolygonShape bodyShape;
		b2FixtureDef bodyFixtureDef;

	 public:
	 	// Abstract Attributes
	 	Color fillColor, outlineColor;
	 	float thickness;

	 	// Functions
		MakeRectangle(b2World& world, Vector2f size, Vector2f position, float rotation = 0, bool isDynamic = true);
		void update();
		Shape& getShape();
	};
}
#endif