#include "cTanks.h"

cTanks::cTanks()
{
}

void cTanks::add(cTextureMgr* theTxtMgr, std::vector<LPCSTR> txtName, SDL_Point posXY, float fruitRot, int fruitVel, int loopPos)
{
	this->theTanks.push_back(new cTank(posXY, fruitRot, fruitVel));
	LPCSTR textName = txtName[static_cast<int>(this->theTanks[loopPos]->getETankType()) + 3];
	this->theTanks[loopPos]->setTexture(theTxtMgr->getTexture(textName));
	this->theTanks[loopPos]->setSpriteDimensions(theTxtMgr->getTexture(textName)->getTWidth(), theTxtMgr->getTexture(textName)->getTHeight());
	this->theTanks[loopPos]->setTankVelocity(100);
	this->theTanks[loopPos]->setActive(true);
}

void cTanks::update(double tankDeltaTime)
{
	for (auto anItem : this->theTanks)
	{
		anItem->update(tankDeltaTime);
	}
}

void cTanks::checkCollisions(SDL_Rect* theBoundingRect)
{
	for (auto anItem : this->theTanks)
	{
		if (anItem->collidedWith(&anItem->getBoundingRect(), theBoundingRect))
		{
			anItem->setActive(false);
		}
	}
}

void cTanks::render(SDL_Renderer* theRenderer)
{
	for (auto anItem : this->theTanks)
	{
		if (anItem->isActive())
		{
			anItem->render(theRenderer, &anItem->getSpriteDimensions(), &anItem->getSpritePos(), anItem->getTankRotation(), &anItem->getSpriteCentre());
		}
		
	}
}

int cTanks::theNumTanks()
{
	this->numTanks = this->theTanks.size();
	return numTanks;
}

int cTanks::theNumActiveTanks()
{
	int active = 0;
	for (auto anItem : this->theTanks)
	{
		if (anItem->isActive() == true)
		{
			active++;
		}
	}
	this->numActiveTanks = active;
	return this->numActiveTanks;
}

SDL_Rect cTanks::getTankBoundingRect(int loopPos)
{
	return this->theTanks[loopPos]->getBoundingRect();
}

bool cTanks::getActive(int loopPos)
{
	return this->theTanks[loopPos]->isActive();
}

void cTanks::setActive(int loopPos, bool active)
{
	this->theTanks[loopPos]->setActive(active);
}

int cTanks::getTanksDestroyed()
{
	this->tanksDestroyed = this->numTanks - this->numActiveTanks;
	return this->tanksDestroyed;
}
