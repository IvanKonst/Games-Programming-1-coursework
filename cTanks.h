#pragma once
#include "cTank.h"
#include "cSprite.h"
#include <vector>

class cTanks
{
private:
	std::vector <cTank*> theTanks;
	int numTanks = 0;
	int numActiveTanks = 0;
	int tanksDestroyed = 0;

public:
	cTanks();
	void add(cTextureMgr* theTxtMgr, std::vector<LPCSTR> txtName, SDL_Point posXY, float tankRot, int tankVel, int loopPos);
	void update(double tankDeltaTime);
	void checkCollisions(SDL_Rect* theBoundingRect);
	void render(SDL_Renderer* theRenderer);
	int theNumTanks();
	int theNumActiveTanks();
	SDL_Rect getTankBoundingRect(int loopPos);
	bool getActive(int loopPos);
	void setActive(int loopPos, bool active);
	int getTanksDestroyed();
};

