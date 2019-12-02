#include "cShells.h"

cShells::cShells()
{
}

void cShells::add(cTextureMgr* theTxtMgr, std::vector<LPCSTR> txtName, SDL_Point posXY, float shellRot, int shellVel, int loopPos)
{
	this->theShells.push_back(new cShell());
	LPCSTR textName = "shell";
	this->theShells[loopPos]->setSpritePos(posXY);
	this->theShells[loopPos]->setShellsRotation(shellRot);
	this->theShells[loopPos]->setTexture(theTxtMgr->getTexture(textName));
	this->theShells[loopPos]->setSpriteDimensions(theTxtMgr->getTexture(textName)->getTWidth(), theTxtMgr->getTexture(textName)->getTHeight());
	this->theShells[loopPos]->setShellsVelocity(shellVel);
	this->theShells[loopPos]->setActive(true);
}

void cShells::update(double shellDeltaTime)
{
	for (auto anItem : this->theShells)
	{
		anItem->update(shellDeltaTime);
	}
}

void cShells::checkCollisions(SDL_Rect* theBoundingRect)
{
	for (auto anItem : this->theShells)
	{
		if (anItem->collidedWith(&anItem->getBoundingRect(), theBoundingRect))
		{
			anItem->setActive(false);
		}
	}
}

void cShells::render(SDL_Renderer* theRenderer)
{
	for (auto anItem : this->theShells)
	{
		if (anItem->isActive())
		{
			anItem->render(theRenderer, &anItem->getSpriteDimensions(), &anItem->getSpritePos(), anItem->getShellsRotation(), &anItem->getSpriteCentre());
		}
		
	}
}

int cShells::theNumShells()
{
	this->numShells = theShells.size();
	return this->numShells;
}

SDL_Rect cShells::getShellBoundingRect(int loopPos)
{
	return this->theShells[loopPos]->getBoundingRect();
}

bool cShells::getActive(int loopPos)
{
	return this->theShells[loopPos]->isActive();
}

void cShells::setActive(int loopPos, bool active)
{
	this->theShells[loopPos]->setActive(active);
}
