#include <SFMl\Graphics.hpp>
#include <vector>
#include <Box2D\Box2D.h>
#include "CharacterController.h"
#include "Pillar.h"

using namespace GalaxyBox;

Pillar::Pillar()
{
	
}

Pillar::Pillar(Vector2f size, Vector2f pos)
{
	this->size = size;
    this->pos = pos;
    this->nextPos.Set(pos.x, pos.y);
}

void Pillar::CreatePillar(b2World& world, bool dynamic)
{	
	MakeRectanglePhysics(size, pos, world, 0.0, dynamic);

    MakeRectangleVisual(size, Color::White, Color::Black, -1);
}