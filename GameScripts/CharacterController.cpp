#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "CharacterController.h"
#include "GameConstants.h"
#include <iostream>
#include <exception>
#include <cmath>
#include <chrono>

using namespace std;
using namespace sf;
using namespace TimeBox;

CharacterController::CharacterController()
{

}

CharacterController::~CharacterController()
{
	//body->GetWorld()->DestroyBody(body);
}

void CharacterController::MakeShapePhysics(Vector2f size, Vector2f& position,  b2World& world, float rotation, bool isDynamic, bool isRectangle, float radius )
{	
	// Box2D
	b2BodyDef bodyDef;
	b2FixtureDef bodyFixtureDef;

	// Define body attributes.
	bodyDef.position = b2Vec2(position.x / PIXEL_PER_METER, position.y / PIXEL_PER_METER);
	position = Vector2f(bodyDef.position.x, bodyDef.position.y);


   if (isDynamic)
      bodyDef.type = b2_dynamicBody; // b2_kinematicBody
   else  
      bodyDef.type = b2_kinematicBody; // b2_staticBody;

  	this->isRectangle = isRectangle;

   	// Define body look.
   if (isRectangle)
   {
		bodyShapeRectangle.SetAsBox((size.x/2)/PIXEL_PER_METER, (size.y/2)/PIXEL_PER_METER);
		bodyFixtureDef.shape = &bodyShapeRectangle;
		// Define body personality.
    	bodyFixtureDef.restitution = 0.3f;
		if (type == TYPE[AgeUp])
			bodyFixtureDef.density = 0.4f;
		else if (type == TYPE[AgeDown])
			bodyFixtureDef.density = 0.3f;
		else
		{
    		bodyFixtureDef.restitution = 0.6f;
			bodyFixtureDef.density = 0.2f;
		}

		bodyFixtureDef.friction = 0.5f;
   }
   else
   {
   		bodyShapeCircle.m_p.Set((size.x/2)/PIXEL_PER_METER, (size.y/2)/PIXEL_PER_METER);
   		bodyShapeCircle.m_radius = radius / PIXEL_PER_METER;
		bodyFixtureDef.shape = &bodyShapeCircle;
		bodyFixtureDef.density = 1;
		bodyFixtureDef.friction = 0;
    	bodyFixtureDef.restitution = 0.8f;
   }
	
   	bodyFixtureDef.userData = this;
   	bodyDef.userData = this;

	// Combine all into one body.
	body = world.CreateBody(&bodyDef);

   	body->character = this;

   	body->SetUserData(this);
   	
	// Create fixture for collisions
	body->CreateFixture(&bodyFixtureDef);
}

void CharacterController::Update() { }

void CharacterController::CheckCollision() { }

void CharacterController::Lerp(b2Vec2 nextPos , float lerpRate, bool& keepMoving)
{
	lerpRate /= (abs(body->GetPosition().x - nextPos.x) + abs(body->GetPosition().y - nextPos.y));


   	b2Vec2 newPos(body->GetPosition().x + ((nextPos.x - body->GetPosition().x) * lerpRate),
   				  body->GetPosition().y + ((nextPos.y - body->GetPosition().y) * lerpRate));


	//cout << " Body Position  " << body->GetPosition().x << " __" << body->GetPosition().y << endl;
	//cout << " New Position   " << newPos.x << " __" << newPos.y << endl;
	//cout << " Next Position   " << nextPos.x << " __" << nextPos.y << endl;
	//cout << " Difference is  " << abs(newPos.x - nextPos.x) << endl << endl;

   	// Condionize for dynamic bodies and static ones
	body->SetTransform(newPos, body->GetAngle());
	
	if (abs(newPos.x - nextPos.x) < 0.1f &&  abs(newPos.y - nextPos.y) < 0.1f)
	{
		keepMoving = false;
		//cout << "done" << endl;
	}

}

void CharacterController::ApplyVelocity(b2Vec2 velo)
{
	if (body->GetLinearVelocity().x < 0)
		velo.Set(velo.x * -1, velo.y);
	else
		velo.Set(abs(velo.x), velo.y);

	if (body->GetLinearVelocity().y < 0)
		velo.Set(velo.x, velo.y * -1);
	else
		velo.Set(velo.x, abs(velo.y));

	body->SetLinearVelocity(velo);
}

void CharacterController::DrawShape(WindowController& gameWindow)
{
	if (isRectangle)
    	gameWindow.Draw(rect);
    else
    	gameWindow.Draw(circle);
}

Shape& CharacterController::GetShape()
{
	if (isRectangle)
    	return rect;
    else
    	return circle;
}
