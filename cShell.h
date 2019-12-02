#pragma once
#include "cSprite.h"
class cShell : public cSprite
{
private:
	int ShellVelocity;
	double ShellRotAngle;

public:
	cShell();
	void initialise();
	void update(double ShellDeltaTime);		// Shell update method
	void setShellsVelocity(int ShellsVel);   // Sets the velocity for the Shell
	int getShellsVelocity();				 // Gets the Shell velocity
	void setShellsRotation(double theRotAngle);   // Sets the rotation angle for the Shell
	double getShellsRotation();				 // Gets the rotation angle for the Shell velocity
};

