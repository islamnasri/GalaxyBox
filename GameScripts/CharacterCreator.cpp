#include "CharacterCreator.h"

using namespace sf;

// Box2D uses meters for simulation, so we need to set how many pixels representing one meter
// We prefer a 2^n value (e.g. 1,2,4,8,16,32,64 etc) because of reasons
// Why? Refer to Computer Graphics
static const float PIXEL_PER_METER = 32.0f;


CharacterCreator::MakeRectangle(b2World& world, Vector2f size, Vector2f position, float rotation, bool isDynamic )
{
	// SFML // Create texture.
	rect = RectangleShape(size);
	rect.setOrigin(Vector2f(size.x/2,size.y/2));
	rect.setFillColor(fillColor);
	rect.setOutlineThickness(thickness);
	rect.setOutlineColor(outlineColor);

	// Box2D
	// Define body attributes.
	bodyDef.position = b2Vec2(position.x/PIXEL_PER_METER, position.y/PIXEL_PER_METER);

   if (isDynamic)
   {
      bodyDef.type = b2_dynamicBody;
   }
   else  
   {
      bodyDef.type = b2_staticBody;
   }

   	// Define body look.
	bodyShape.SetAsBox((size.x/2)/PIXEL_PER_METER, (size.y/2)/PIXEL_PER_METER);

	// Define body personality.
	bodyFixtureDef.shape = &bodyShape;
	bodyFixtureDef.density = 0.3f;
	bodyFixtureDef.friction = 0.5f;

	// Cobine all into one body.
	body = world.CreateBody(&bodyDef);
	body->CreateFixture(&bodyFixtureDef);
}

void CharacterCreator::update()
{
	// Box2D uses radians for rotation, SFML uses degree
    rect.setRotation( body->GetAngle() * 180/b2_pi);
    rect.setPosition( body->GetPosition().x*PIXEL_PER_METER, body->GetPosition().y*PIXEL_PER_METER);
}

Shape& CharacterCreator::getShape()
{
	return rect;
}