#ifndef _GAME_H
#define _GAME_H

/*
==================================================================================
cGame.h
==================================================================================
*/

#include <SDL.h>

// Game specific includes
#include "GameSpecific.h"
#include<random>

using namespace std;

class cGame
{
public:
	cGame();

	void initialise(SDL_Renderer* theRenderer);
	void run(SDL_Renderer* theRenderer);
	void cleanUp(SDL_Window* theSDLWND);
	void render(SDL_Renderer* theRenderer);
	void update();
	void update(double theDeltaTime);
	bool getInput(bool theLoop);
	double getElapsedSeconds();

	static cGame* getInstance();

private:

	static cGame* pInstance;
	// for framerates
	time_point< high_resolution_clock > m_lastTime;
	time_point< high_resolution_clock > m_CurrentTime;
	duration< double > deltaTime;
	bool loop;

	/* Let the computer pick a random number */
	random_device rd;    // non-deterministic engine 
	mt19937 gen{ rd() }; // deterministic engine. For most common uses, std::mersenne_twister_engine, fast and high-quality.
	uniform_int_distribution<> spriteRandom{ 0, 9 };

	// Sprites for displaying background and rocket textures
	cSprite spriteBkgd;
	// game related variables
	vector<LPCSTR> textureName;
	vector<LPCSTR> textName;
	vector<LPCSTR> texturesToUse;
	// Fonts to use
	vector<LPCSTR> fontList;
	vector<LPCSTR> fontsToUse;
	// Text for Game
	vector<LPCSTR> gameTextNames;
	vector<LPCSTR> gameTextList;
	vector<LPCSTR> highScoreTextures;
	// Game Sounds
	vector<LPCSTR> soundList;
	vector<soundType> soundTypes;
	vector<LPCSTR> soundsToUse;
	// Create vector array of button textures
	vector<LPCSTR> btnNameList;
	vector<LPCSTR> btnTexturesToUse;
	vector<SDL_Point> btnPos;
	vector <cButton> theButtons;
	// Game objects
	int renderWidth = 0, renderHeight = 0;
	SDL_Rect pos = { 0,0,0,0 };
	FPoint scale = { 0,0 };
	SDL_Rect aRect = {0,0,0,0};
	SDL_Color aColour = {255, 255, 255};
	cTexture* tempTextTexture;
	bool renderText = false;

	cTanks theTanks;
	cShells theShells;
	cTank thePlayer;

	int tanksDestroyed = 0;
	std::string strScore = "";
	gameState theGameState = gameState::menu;
	btnTypes theBtnType = btnTypes::exit;
	SDL_Point theAreaClicked = {0,0};
	bool gameOver = false;
};

#endif
