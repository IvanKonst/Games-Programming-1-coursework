#include "cShell.h"
/*
=================
cShell.cpp
- Header file for class definition - IMPLEMENTATION
=================
*/
cShell::cShell()
{
	ShellVelocity = 0;
	ShellRotAngle = 0;
	this->setActive(false);
}

/*
=================================================================
Initialise the sprite variables
=================================================================
*/

void cShell::initialise()
{
	ShellVelocity = 0;
	ShellRotAngle = 0;
}

/*
=================================================================
Update the sprite position
=================================================================
*/

void cShell::update(double ShellDeltaTime)
{

	SDL_Rect currentSpritePos = this->getSpritePos();

	auto rads = PI / 180.0f * this->getShellsRotation();

	currentSpritePos.y -= (int)(this->getShellsVelocity() * ShellDeltaTime);

	this->setSpritePos({ currentSpritePos.x , currentSpritePos.y });
	this->setBoundingRect();
	// The line below is for debugging purposes and can be safely removed.
	//std::cout << "Shell: " << currentSpritePos.x << "," << currentSpritePos.y << " Rot " << this->getSpriteRotAngle() << " DT " << ShellDeltaTime << "\n";
}
/*
=================================================================
  Sets the velocity for the Shell
=================================================================
*/
void cShell::setShellsVelocity(int ShellsVel)
{
	ShellVelocity = ShellsVel;
}
/*
=================================================================
  Gets the Shell velocity
=================================================================
*/
int cShell::getShellsVelocity()
{
	return ShellVelocity;
}
/*
=================================================================
Sets the rotation angle for the Shell
=================================================================
*/
void cShell::setShellsRotation(double theRotAngle)
{
	ShellRotAngle = theRotAngle;
}
/*
=================================================================
Gets the rotation angle for the Shell
=================================================================
*/
double cShell::getShellsRotation()
{
	return ShellRotAngle;
}
