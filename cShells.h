#pragma once
#include "cShell.h"
#include <vector>

class cShells
{
private:
	std::vector <cShell*> theShells;
	int numShells = 0;

public:
	cShells();
	void add(cTextureMgr* theTxtMgr, std::vector<LPCSTR> txtName, SDL_Point posXY, float shellRot, int shellVel, int loopPos);
	void update(double shellDeltaTime);
	void checkCollisions(SDL_Rect* theBoundingRect);
	void render(SDL_Renderer* theRenderer);
	int theNumShells();
	SDL_Rect getShellBoundingRect(int loopPos);
	bool getActive(int loopPos);
	void setActive(int loopPos, bool active);
};

