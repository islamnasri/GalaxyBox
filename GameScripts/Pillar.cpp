#include <SFMl\Graphics.hpp>
#include <vector>
#include <Box2D\Box2D.h>
#include "CharacterController.h"
#include "Pillar.h"
#include "GalaxyBox.h"
#include <iostream>

using namespace std;
using namespace GalaxyBox;

Pillar::Pillar()
{

}

Pillar::Pillar(Vector2f size, Vector2f pos)
{
	this->size = size;

    this->pos = pos;

	type = Wall;
}

void Pillar::CreatePillar(b2World& world, bool dynamic)
{	
    bodyFixtureDef.restitution = 0.2f;

	MakeShapePhysics(size, pos, world, 0.0, dynamic);

	body->SetFixedRotation(true);

    MakeRectangleVisual(size, Color::White, Color::Black, -1);
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
