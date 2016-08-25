#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "CharacterController.h"
#include "GameConstants.h"
#include "GalaxyBox.h"
#include <iostream>
#include <exception>
#include <cmath>
#include <chrono>

using namespace std;
using namespace sf;
using namespace GalaxyBox;

void CharacterController::MakeRectanglePhysics(Vector2f size, Vector2f& position,  b2World& world, float rotation, bool isDynamic )
{	
	rect = RectangleShape(size);

	// Box2D
	// Define body attributes.
	bodyDef.position = b2Vec2(position.x / PIXEL_PER_METER, position.y / PIXEL_PER_METER);
	position = Vector2f(bodyDef.position.x, bodyDef.position.y);


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

void CharacterController::MakeRectangleVisual(Vector2f size, Color fillColor, Color outlineColor, float thickness)
{
	// SFML // Create texture.
	rect.setSize(size);
	rect.setOrigin(Vector2f(size.x/2,size.y/2));
	rect.setFillColor(fillColor);
	rect.setOutlineThickness(thickness);
	rect.setOutlineColor(outlineColor);
}

void CharacterController::Update()
{
	
	if (Keyboard::isKeyPressed(Keyboard::Space))
	{
		//body->SetTransform(b2Vec2(body->GetPosition().x + 0.2f,body->GetPosition().y + 5), body->GetAngle());
		body->SetLinearVelocity(b2Vec2(body->GetPosition().x + 0.2f,body->GetPosition().y));
	}
	
	// body->SetFixedRotation(true);

	// Box2D uses radians for rotation, SFML uses degree
    rect.setRotation( body->GetAngle() * 180/b2_pi);
    // Get meters in Box2D scale and multiply by the no. of pixels_per_meter to pixels for SFML objects.
    rect.setPosition( body->GetPosition().x*PIXEL_PER_METER, body->GetPosition().y*PIXEL_PER_METER);

}

void CharacterController::Lerp(b2Vec2 nextPos , float lerpRate, bool& keepMoving)
{
	lerpRate /= (abs(body->GetPosition().x - nextPos.x) + abs(body->GetPosition().y - nextPos.y));


   	b2Vec2 newPos(body->GetPosition().x + ((nextPos.x - body->GetPosition().x) * lerpRate),
   				  body->GetPosition().y + ((nextPos.y - body->GetPosition().y) * lerpRate));


	cout << " Body Position  " << body->GetPosition().x << " __" << body->GetPosition().y << endl;
	cout << " New Position   " << newPos.x << " __" << newPos.y << endl;
	cout << " Next Position   " << nextPos.x << " __" << nextPos.y << endl;
	cout << " Difference is  " << abs(newPos.x - nextPos.x) << endl << endl;

	body->SetTransform(newPos, body->GetAngle());
	
	if (abs(newPos.x - nextPos.x) < 0.1f &&  abs(newPos.y - nextPos.y) < 0.1f)
	{
		keepMoving = false;
		cout << "done" << endl;
	}

}

void CharacterController::PushWith(b2Vec2 impulse, b2Vec2 nextPos , bool& keepMoving)
{
	body->ApplyLinearImpulse(impulse, body->GetWorldCenter(), true);

	cout << " Body Position  " << body->GetPosition().x << " __" << body->GetPosition().y << endl;
	cout << " Next Position  " << nextPos.x << " __" << nextPos.y << endl;

	if (abs(body->GetPosition().x - nextPos.x) < 3 && abs(body->GetPosition().y - nextPos.y) < 3)
	{
		keepMoving = false;
		cout << "done" << endl;
	}
}

Shape& CharacterController::GetShape()
{
	return rect;
}