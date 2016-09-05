#include <SFMl\Graphics.hpp>
#include <Box2D\Box2D.h>
#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <ctime>

#include "Square.h"
#include "WindowController.h"
#include "GameConstants.h"
#include "ContactListener.h"

using namespace std;
using namespace GalaxyBox;

Square::Square()
{
	
}

Square::~Square()
{

}

Square::Square(int imageNo, Vector2f size, Vector2f pos, OBJECT_TYPES type, b2World& world, bool isPlatform)
{
	this->size = size;

    this->pos = pos;

    this->type = TYPE[type];

    this->isPlatform = isPlatform;

    if (isPlatform)
    {

    	MakeShapePhysics(size, pos, world,0, false);

		rect = RectangleShape(size);

    	if (type == AgeUp)
    		MakeSquareVisual(size, Color::White, Color::Black, -1);
    	else
    		MakeSquareVisual(size, Color::Red, Color::Black, -1);

    	body->SetGravityScale(0.2f);
    	body->SetFixedRotation(true);
    	body->SetLinearVelocity(b2Vec2(0, 5));
  		changeTypeMaxTimer = (rand() % 200) + 200;
    }
    else
    {
    	MakeShapePhysics(size, pos, world, 0, true);
    	MakeSquareVisual(size,imageNo);
    }
}

void Square::MakeSquareVisual(Vector2f size, int imageNo)
{
	tex = new Texture();

	rect = RectangleShape(size);
	if (tex->loadFromFile(RESOURCES_IMAGES[imageNo]))
	{
		tex->loadFromFile(RESOURCES_IMAGES[imageNo]);
		rect.setTexture(tex);
	}

	rect.setOrigin(Vector2f(size.x/2,size.y/2));
}

void Square::MakeSquareVisual(Vector2f size, Color fillColor, Color outlineColor, float thickness)
{
	// SFML // Create texture.
	rect.setSize(size);
	rect.setOrigin(Vector2f(size.x/2,size.y/2));
	rect.setFillColor(fillColor);
	rect.setOutlineThickness(thickness);
	rect.setOutlineColor(outlineColor);
}


void Square::Update(RenderWindow& window)
{
	if (type == TYPE[Player])
	{

		if (followUpAge == age)
		{
			ageCounter++;
			if (ageCounter >= 500)
			{
				if (age > 5)
					age++;
				else
					age--;
			}
		}
		else
		{
			followUpAge = age;
			ageCounter = 0;
		}

		if (Mouse::isButtonPressed(Mouse::Left))
		{
			if (!startCountingMouseDistance)
			{
	    		startCountingMouseDistance = true;
	    		mouseClickPos = Mouse::getPosition(window);
			}
		}
		else
		{
	    	if (startCountingMouseDistance)
	    	{
	    		startCountingMouseDistance = false;
	    		distanceToTravel = Vector2f(Mouse::getPosition(window).x - mouseClickPos.x, Mouse::getPosition(window).y - mouseClickPos.y);

				body->SetLinearVelocity(b2Vec2(distanceToTravel.x / PIXEL_PER_METER, distanceToTravel.y / PIXEL_PER_METER));
	    	}
		}
	}

    rect.setRotation( body->GetAngle() * 180/b2_pi );
    rect.setPosition( body->GetPosition().x * PIXEL_PER_METER, body->GetPosition().y * PIXEL_PER_METER );
}

void Square::UpdatePlatform()
{
	changeTypeTimer += 1;

	if ( changeTypeTimer > changeTypeMaxTimer)
	{
		this->type = (this->type == TYPE[AgeUp])? TYPE[AgeDown] : TYPE[AgeUp];

		if (type == TYPE[AgeUp])
    		MakeSquareVisual(size, Color::White, Color::Black, -1);
    	else
    		MakeSquareVisual(size, Color::Red, Color::Black, -1);

		changeTypeTimer = 0;
	}
}


void Square::CheckCollision(b2World& world)
{
	b2Contact* contact;
	CharacterController *A;
	for (b2ContactEdge* edge = body->GetContactList(); edge; edge = edge->next)
	{
		contact = edge->contact;

		if (contact->IsTouching())
		{
			if ( edge->other->GetFixtureList()->GetDensity() == 0.4f) // Age Up
				age++;
			else if ( edge->other->GetFixtureList()->GetDensity() == 0.3f) // Age Down
				age--;
			else
				age -= 2;
			
    		if ( age <= 0 || age >= 10)
    			alive = false;
		}
	}
}

void Square::MoveWithConstantSpeed()
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

bool Square::TimeToDie()
{
	if (GetShape().getPosition().y > WINDOW_SIZE_Y)
		return true;

	return false;
}

void Square::Restart()
{
	body->SetTransform(b2Vec2(this->pos.y / PIXEL_PER_METER, this->pos.y / PIXEL_PER_METER), 0);
	age = 5;
}