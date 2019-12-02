#include "cTank.h"

cTank::cTank()
{
	this->eTankType = tankType::blue;
	this->tankPosition = { 0,0 };
	this->setSpritePos(this->tankPosition);
	this->tankRotation = 0.0f;
	this->tankTypeStr = "Blue";
	this->tankValue = 0;
	this->tankVelocity = 0;
	this->setActive(false);
}

cTank::cTank(SDL_Point posXY, float thetankRot, tankType theEtankType, int theVel)
{
	this->eTankType = theEtankType;
	this->tankPosition = posXY;
	this->setSpritePos(this->tankPosition);
	this->tankRotation = thetankRot;
	this->setTankTypeStr(this->eTankType);
	this->genTankValue(this->eTankType);
	this->tankVelocity = theVel;
	this->setActive(true);
}

cTank::cTank(SDL_Point posXY, float thetankRot, int theVel)
{
	this->eTankType = this->genRandomTankType();
	this->tankPosition = posXY;
	this->setSpritePos(this->tankPosition);
	this->tankRotation = thetankRot;
	this->setTankTypeStr(this->eTankType);
	this->genTankValue(this->eTankType);
	this->tankVelocity = theVel;
	this->setActive(true);
}

void cTank::update(double tankDeltaTime)
{
	if (this->isActive())
	{
		SDL_Rect currentSpritePos = this->getSpritePos();

		auto rads = PI / 180.0f * this->getTankRotation();

		currentSpritePos.y += (int)(this->getTankVelocity() * tankDeltaTime);

		if (currentSpritePos.y > 770)
		{
			currentSpritePos.y = 0 - this->getSpriteDimensions().h;
		}

		this->setSpritePos({ currentSpritePos.x , currentSpritePos.y });
		this->setBoundingRect();
		// The line below is for debugging purposes and can be safely removed.
		std::cout << currentSpritePos.x << "," << currentSpritePos.y << " Rot " << this->getTankRotation() << " DT " << tankDeltaTime << "\n";
	}
}

void cTank::update(double tankDeltaTime, std::string direction)
{
	SDL_Rect currentSpritePos = this->getSpritePos();

	auto rads = PI / 180.0f * this->getTankRotation();

	if (direction == "leftRight")
	{
		currentSpritePos.x += (int)(this->getTankVelocity() * tankDeltaTime);
	}
	else
	{
		currentSpritePos.y += (int)(this->getTankVelocity() * tankDeltaTime);
	}

	this->setSpritePos({ currentSpritePos.x , currentSpritePos.y });
	this->setBoundingRect();
	// The line below is for debugging purposes and can be safely removed.
	std::cout << currentSpritePos.x << "," << currentSpritePos.y << " Rot " << this->getTankRotation() << " DT " << tankDeltaTime << "\n";

}

float cTank::getTankRotation()
{
	return this->tankRotation;
}

void cTank::setTankRotation(float thetankRot)
{
	this->tankRotation = thetankRot;
}

SDL_Point cTank::getTankPos()
{
	return this->tankPosition;
}

void cTank::setTankPos(SDL_Point thetankPos)
{
	this->tankPosition = thetankPos;
}

std::string cTank::getTankTypeStr()
{
	return this->tankTypeStr;
}

LPCSTR cTank::getTankTypeStrLPC()
{
	return this->tankTypeL;
}

void cTank::setTankTypeStr(std::string thetankTypeStr)
{
	this->tankTypeStr = thetankTypeStr;
}

void cTank::setTankTypeStr(tankType thetankType)
{
	switch (thetankType)
	{
	case tankType::blue:
		this->tankTypeStr = "blue";
		break;
	case tankType::brown:
		this->tankTypeStr = "brown";
		break;
	case tankType::turq:
		this->tankTypeStr = "turq";
		break;
	case tankType::green:
		this->tankTypeStr = "green";
		break;
	default:
		this->tankTypeStr = "Error";
	}
	this->tankTypeL = this->tankTypeStr.c_str();
}

tankType cTank::getETankType()
{
	return this->eTankType;
}

void cTank::setETankType(tankType theEtankType)
{
	this->eTankType = theEtankType;
}

int cTank::getTankValue()
{
	return this->tankValue;
}

void cTank::setTankValue(int thetankValue)
{
	this->tankValue = thetankValue;
}

int cTank::getTankVelocity()
{
	return this->tankVelocity;
}

void cTank::setTankVelocity(int thetankVelocity)
{
	this->tankVelocity = thetankVelocity;
}

tankType cTank::genRandomTankType()
{
	return static_cast<tankType>(randTank(gen));
}

void cTank::genTankValue(tankType thetankType)
{
	switch (thetankType)
	{
	case tankType::blue:
		this->tankValue = 50;
		break;
	case tankType::brown:
		this->tankValue = 75;
		break;
	case tankType::turq:
		this->tankValue = 100;
		break;
	case tankType::green:
		this->tankValue = 125;
		break;
	default:
		this->tankValue = 0;
	}
}
