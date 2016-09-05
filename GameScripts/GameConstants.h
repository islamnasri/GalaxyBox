
#ifndef GAME_CONSTANTS_H
#define GAME_CONSTANTS_H

#include <SFML\Graphics.hpp>
#include <Box2D\Box2D.h>
#include <windows.h>
#include <array>

//#include "Ball.h"

using namespace std;
using namespace sf;

namespace GalaxyBox
{
	static const int WINDOW_SIZE_X = GetSystemMetrics(SM_CXSCREEN)/1.3f;

	static const int WINDOW_SIZE_Y = GetSystemMetrics(SM_CYSCREEN)/1.2f;

   	static const int SCREEN_CENTER_X = WINDOW_SIZE_X/2;

   	static const int SCREEN_CENTER_Y = WINDOW_SIZE_Y/2;

   	// Box2D uses meters for simulation, so we need to set how many pixels representing one meter
	// We prefer a 2^n value (e.g. 1,2,4,8,16,32,64 etc)
	// You can say the less it goes the heavier the object.
	static const float PIXEL_PER_METER = 32;

	static float FIXED_TIME_STEP = 0.02f; // 50 times per second

	static const float X_AXIS_GRAVITY = 0.0f;

	static const float Y_AXIS_GRAVITY = 9.81f;

	static float WORLD_VELOCITY_RATE = 8;

	static float WORLD_POSITION_RATE = 6;

	static const b2Vec2 gravity(X_AXIS_GRAVITY,Y_AXIS_GRAVITY);

	static const array<string,5> RESOURCES_IMAGES = 
	{
	 "Resources/ball.png", 
	 "Resources/bg.jpg",
	 "Resources/speed.jpg",
	 "Resources/invert.jpg",
	 "Resources/kill.jpg"
	};
	
	static const array<string,5> RESOURCES_FONTS = 
	{
		"Resources/04b03.ttf"
	};

	static Font GLOBAL_FONT;
	
	enum OBJECT_TYPES 
	{
		Player = 0,
		Wall = 1,
		AgeUp = 2,
		AgeDown = 3,
	};

	static const array<string,4> TYPE = 
	{
		"Player",
		"Wall",
		"AgeUp",
		"AgeDown",
	};
}

#endif
