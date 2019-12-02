#pragma once
#include "GameConstants.h"
#include <random>
#include "cSprite.h"
class cTank : public cSprite
{
private:
	float tankRotation = 0.0f;
	SDL_Point tankPosition = { 0,0 };
	std::string tankTypeStr = "";
	LPCSTR tankTypeL = tankTypeStr.c_str();
	tankType eTankType = tankType::blue;
	int tankValue = 0;
	int tankVelocity = 0;

	/* Let the computer pick a random number */
	random_device rd;    // non-deterministic engine 
	mt19937 gen{ rd() }; // deterministic engine. For most common uses, std::mersenne_twister_engine, fast and high-quality.
	uniform_int_distribution<> randTank{ 0, 3 }; // Range apple to strawberry

public:
	cTank();
	cTank(SDL_Point posXY, float theTankRot, tankType theETankType, int theVel);
	cTank(SDL_Point posXY, float theTankRot, int theVel);
	void update(double tankDeltaTime);
	void update(double tankDeltaTime, std::string direction);
	float getTankRotation();
	void setTankRotation(float theTankRot);
	SDL_Point getTankPos();
	void setTankPos(SDL_Point theTankPos);
	std::string getTankTypeStr();
	LPCSTR getTankTypeStrLPC();
	void setTankTypeStr(std::string theTankTypeStr);
	void setTankTypeStr(tankType theTankType);
	tankType getETankType();
	void setETankType(tankType theETankType);
	int getTankValue();
	void setTankValue(int theTankValue);
	int getTankVelocity();
	void setTankVelocity(int theTankVelocity);
	tankType genRandomTankType();
	void genTankValue(tankType theTankType);
};

