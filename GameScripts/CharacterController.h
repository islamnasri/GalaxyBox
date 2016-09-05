
#ifndef CHARACTER_CREATOR_H
#define CHARACTER_CREATOR_H



#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include <string>
#include "GameConstants.h"
#include "WindowController.h"


using namespace std;
using namespace sf;

namespace GalaxyBox
{
	class CharacterController : public b2Character
	{
	 protected:
		b2PolygonShape bodyShapeRectangle;
		b2CircleShape bodyShapeCircle;
		RectangleShape rect;
		CircleShape circle;
  		Vector2f size;

	 public:
	 	// Abstract Attributes
		b2Body* body;
	 	Vector2f pos;
  		b2Vec2 velocity;
  		string type;
		bool destroy = false;
		bool isRectangle;


	 	// Functions
	 	CharacterController();
	 	~CharacterController();
		void MakeShapePhysics(Vector2f size, Vector2f& position, b2World& world, float rotation = 0, bool isDynamic = true, bool isRectangle = true, float radius = 0);
		virtual void Update();
		virtual void CheckCollision();
		void Lerp(b2Vec2 nextPos, float lerpRate, bool& done);
		void ApplyVelocity(b2Vec2 velo);
		void DrawShape(WindowController& gameWindow);
		Shape& GetShape();
	};
}
#endif