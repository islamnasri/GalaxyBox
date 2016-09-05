#include <SFMl\Graphics.hpp>
#include <vector>
#include <Box2D\Box2D.h>
#include "CharacterController.h"
#include "Pillar.h"
#include <iostream>

using namespace std;
using namespace TimeBox;

Pillar::Pillar()
{

}

Pillar::Pillar(Vector2f size, Vector2f pos)
{
	this->size = size;

    this->pos = pos;

	this->type = TYPE[Wall];
}

void Pillar::CreatePillar(b2World& world, bool dynamic)
{	
	MakeShapePhysics(size, pos, world, 0.0, dynamic);

	body->SetFixedRotation(true);

    MakeRectangleVisual(size, Color::Magenta, Color::Magenta, -1);
}


void Pillar::MakeRectangleVisual(Vector2f size, Color fillColor, Color outlineColor, float thickness)
{
	rect = RectangleShape(size);

	// SFML // Create texture.
	rect.setSize(size);
	rect.setOrigin(Vector2f(size.x/2,size.y/2));
	rect.setFillColor(fillColor);
	rect.setOutlineThickness(thickness);
	rect.setOutlineColor(outlineColor);
}

void Pillar::Update()
{
	// Box2D uses radians for rotation, SFML uses degree
    rect.setRotation( body->GetAngle() * 180/b2_pi );
    // Get meters in Box2D scale and multiply by the no. of pixels_per_meter to pixels for SFML objects.
    rect.setPosition( body->GetPosition().x*PIXEL_PER_METER, body->GetPosition().y*PIXEL_PER_METER );
}