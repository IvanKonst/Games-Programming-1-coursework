/*
=================
cRocket.cpp
- Header file for class definition - IMPLEMENTATION
=================
*/
#include "cRocket.h"

/*
=================================================================
Initialise the sprite variables
=================================================================
*/

void cRocket::initialise()
{
	rocketVelocity = 0;
	rocketRotAngle = 0;
}

//void cRocket::render()
//{
//}
/*
=================================================================
Update the sprite position
=================================================================
*/

void cRocket::update(double deltaTime)
{

	SDL_Rect currentSpritePos = this->getSpritePos();

	auto rads = PI / 180.0f * this->getRocketRotation();

	currentSpritePos.x -= (int)(sin(rads)*this->getRocketVelocity() * deltaTime); //rocketVelocity.x;
	currentSpritePos.y += (int)(cos(rads)*this->getRocketVelocity() * deltaTime); //rocketVelocity.y;


	this->setSpritePos({ currentSpritePos.x , currentSpritePos.y}); // , currentSpritePos.w, currentSpritePos.h 
	this->rocketVelocity = 0;
}
/*
=================================================================
  Sets the velocity for the rocket
=================================================================
*/
void cRocket::setRocketVelocity(int rocketVel)
{
	rocketVelocity = rocketVel;
}
/*
=================================================================
  Gets the rocket velocity
=================================================================
*/
int cRocket::getRocketVelocity()
{
	return rocketVelocity;
}
/*
=================================================================
Sets the rotation angle for the rocket
=================================================================
*/
void cRocket::setRocketRotation(double theRotAngle)
{
	rocketRotAngle = theRotAngle;
}
/*
=================================================================
Gets the rotation angle for the rocket
=================================================================
*/
double cRocket::getRocketRotation()
{
	return rocketRotAngle;
}
