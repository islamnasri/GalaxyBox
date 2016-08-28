#include <SFMl\Graphics.hpp>
#include <vector>
#include <string>
#include <cmath>
#include <Box2D\Box2D.h>
#include "Ball.h"
#include "GalaxyBox.h"

using namespace std;
using namespace GalaxyBox;

Ball::Ball()
{
	
}

Ball::Ball(int imageNo, Vector2f size, Vector2f pos, float radius, OBJECT_TYPES type, b2World& world)
{
	this->size = size;

    this->pos = pos;

    this->type = type;

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

void Ball::Update(bool isSpeedConstant)
{
	if (Keyboard::isKeyPressed(Keyboard::Space))
		body->SetLinearVelocity(b2Vec2(-10, 10));

	if (isSpeedConstant)
		MoveWithConstantSpeed();

	
	//CheckCollision(world.GetBodyList());

    circle.setRotation( body->GetAngle() * 180/b2_pi );
    circle.setPosition( body->GetPosition().x * PIXEL_PER_METER, body->GetPosition().y * PIXEL_PER_METER );
}

void Ball::CheckCollision()
{
	b2Contact* c;
	for (b2ContactEdge* ce = body->GetContactList(); ce; ce = ce->next)
	{
		c = ce->contact;
		if (c->IsTouching() == true)
		{
			if (((CharacterController*)(c->GetFixtureB()->GetBody()->GetUserData()))->type == SpeedBooster)
			{
				ApplyVelocity( ((CharacterController*) (c->GetFixtureA()->GetBody()->GetUserData()))->velocity);
				cout << "SpeedBooster" << endl;
			}
		}
	}
}

void Ball::ApplyVelocity(b2Vec2 velo)
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

void Ball::DrawBall(WindowController& gameWindow)
{
    gameWindow.Draw(GetCircle());
}
