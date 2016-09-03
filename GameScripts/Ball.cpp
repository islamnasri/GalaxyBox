#include <SFMl\Graphics.hpp>
#include <Box2D\Box2D.h>
#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <ctime>

#include "Ball.h"
#include "WindowController.h"
#include "GameConstants.h"
#include "ContactListener.h"

using namespace std;
using namespace GalaxyBox;

Ball::Ball()
{
	
}

Ball::~Ball()
{

}

Ball::Ball(int imageNo, Vector2f size, Vector2f pos, float radius, string type, b2World& world)
{
	this->size = size;

    this->pos = pos;

    this->type = type;

	//bodyDef.bullet = true;
    MakeShapePhysics(size, pos, world, 0, true,false, radius);

    MakeCircleVisual(size,imageNo, radius);
}

void Ball::MakeCircleVisual(Vector2f size, int imageNo, float radius)
{
	tex = new Texture();

	circle = CircleShape(radius);
	if (tex->loadFromFile(RESOURCES_IMAGES[imageNo]))
	{
		tex->loadFromFile(RESOURCES_IMAGES[imageNo]);
		circle.setTexture(tex);
	}

	circle.setOrigin(Vector2f(size.x/2,size.y/2));
}

void Ball::Update()
{
	if (Keyboard::isKeyPressed(Keyboard::Space))
		body->SetLinearVelocity(b2Vec2((rand() % 20) - 10, (rand() % 20) - 10));

	if (isSpeedConstant)
		MoveWithConstantSpeed();

	if (type == TYPE[Player]) CheckCollision();

    circle.setRotation( body->GetAngle() * 180/b2_pi );
    circle.setPosition( body->GetPosition().x * PIXEL_PER_METER, body->GetPosition().y * PIXEL_PER_METER );
}


void Ball::CheckCollision()
{
	// you have a problem with the vector objects returnung random info
	// most probably because they're pointing at the wrong address but WHY???.
	/*
	vector<MyContact>::iterator pos;
      for(pos = contactManager->_contacts.begin(); pos != contactManager->_contacts.end(); ++pos) 
        {
          MyContact contact = *pos;
       	
          	cout << "Ball hitA " << ((CharacterController*) contact.fixtureB->GetUserData())->type << endl;
        }*/

	
	b2Contact* contact;
	CharacterController *A, *B;
	for (b2ContactEdge* edge = body->GetContactList(); edge; edge = edge->next)
	{
		contact = edge->contact;

		if (contact->IsTouching())
		{

			A = (CharacterController*) contact->GetFixtureA()->GetUserData();
			if (A != NULL)
				cout << "Value A " << A->type << endl;

		}
	}
}

void Ball::MoveWithConstantSpeed()
{
	if (abs(body->GetLinearVelocity().x) < abs(velocity.x))
		{
			if (body->GetLinearVelocity().x < 0)
				velocity.Set(velocity.x * -1, velocity.y);
			else
				velocity.Set(abs(velocity.x), velocity.y);
		}

		if (abs(body->GetLinearVelocity().y) < abs(velocity.y))
		{
			if (body->GetLinearVelocity().y < 0)
				velocity.Set(velocity.x, velocity.y * -1);
			else
				velocity.Set(velocity.x, abs(velocity.y));
		}

		body->SetLinearVelocity(velocity);
}
