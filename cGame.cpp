/*
==================================================================================
cGame.cpp
==================================================================================
*/
#include "cGame.h"

cGame* cGame::pInstance = NULL;
static cTextureMgr* theTextureMgr = cTextureMgr::getInstance();
static cFontMgr* theFontMgr = cFontMgr::getInstance();
static cSoundMgr* theSoundMgr = cSoundMgr::getInstance();
static cButtonMgr* theButtonMgr = cButtonMgr::getInstance();


/*
=================================================================================
Constructor
=================================================================================
*/
cGame::cGame()
{

}
/*
=================================================================================
Singleton Design Pattern
=================================================================================
*/
cGame* cGame::getInstance()
{
	if (pInstance == NULL)
	{
		pInstance = new cGame();
	}
	return cGame::pInstance;
}


void cGame::initialise(SDL_Renderer* theRenderer)
{
	// Get width and height of render context
	SDL_GetRendererOutputSize(theRenderer, &renderWidth, &renderHeight);
	this->m_lastTime = high_resolution_clock::now();
	// Clear the buffer with a black background
	SDL_SetRenderDrawColor(theRenderer, 0, 0, 0, 255);
	SDL_RenderPresent(theRenderer);
	
	theTextureMgr->setRenderer(theRenderer);
	theFontMgr->initFontLib();
	theSoundMgr->initMixer();	

	// Store the textures
	textureName = { "theBackground","player","shell", "blue", "brown", "turq", "green", "openingScreen", "endScreen","instructionsScreen"};
	texturesToUse = { "Images/Bkg/Spacec.png","Images/Sprites/Player.png", "Images/Sprites/Firea.png",
		"Images/Sprites/Spaceship1.png","Images/Sprites/Spaceship1.png","Images/Sprites/Spaceship1.png",
		"Images/Sprites/Spaceship1.png", "Images/Bkg/Spaceb.png", "Images/Bkg/Spaceb.png","Images/Bkg/Spaceb.png"  };
	for (unsigned int tCount = 0; tCount < textureName.size(); tCount++)
	{	
		theTextureMgr->addTexture(textureName[tCount], texturesToUse[tCount]);
	}
	aColour = { 228, 213, 238, 255 };
	// Create textures for Game Dialogue (text)
	fontList = { "rocket", "digital" };
	fontsToUse = { "Fonts/BlackPearl.ttf", "Fonts/BlackPearl.ttf" };
	for (unsigned int fonts = 0; fonts < fontList.size(); fonts++)
	{
		if (fonts == 0)
		{
			theFontMgr->addFont(fontList[fonts], fontsToUse[fonts], 48);
		}
		else
		{
			theFontMgr->addFont(fontList[fonts], fontsToUse[fonts], 36);
		}
	}
	// Create text Textures
	gameTextNames = { "TitleTxt", "score", "GameOver","Title", "instructions","goal","instructions2", "score2"};
	gameTextList = { "Cosmic Rebellion", "Score: ", "Game Over","Cosmic Rebellion","Use W A S D - to move","Goal: Kill all the ships","Space - to shoot","Score: "};
	for (unsigned int text = 0; text < gameTextNames.size(); text++)
	{
		if (text == 0 )
		{
			theTextureMgr->addTexture(gameTextNames[text], theFontMgr->getFont("rocket")->createTextTexture(theRenderer, gameTextList[text],textType::solid,
				{ 255, 255, 0, 255 }, { 0, 0, 0, 0 }));
		}
		else
		{
			theTextureMgr->addTexture(gameTextNames[text], theFontMgr->getFont("digital")->createTextTexture(theRenderer, gameTextList[text],textType::solid,
				{ 255, 255, 0, 255 }, { 0, 0, 0, 0 }));
		}
	}
	// Load game sounds
	soundList = { "theme", "click", "fire" };
	soundTypes = { soundType::music, soundType::sfx, soundType::sfx };
	soundsToUse = { "Audio/Theme/GameMusic.mp3", "Audio/SFX/ClickOn.wav", "Audio/SFX/Laser.mp3"};
	for (unsigned int sounds = 0; sounds < soundList.size(); sounds++)
	{
		theSoundMgr->add(soundList[sounds], soundsToUse[sounds], soundTypes[sounds]);
	}

	btnNameList = { "exit_btn", "instructions_btn", "load_btn", "menu_btn", "play_btn", "save_btn", "settings_btn" };
	btnTexturesToUse = { "Images/Buttons/button_exit.png", "Images/Buttons/button_instructions.png", "Images/Buttons/button_load.png", "Images/Buttons/button_menu.png", "Images/Buttons/button_play.png", "Images/Buttons/button_save.png", "Images/Buttons/button_settings.png" };
	btnPos = { { 400, 375 }, { 400, 300 }, { 400, 300 }, { 500, 500 }, { 400, 300 }, { 740, 500 }, { 400, 300 } };
	for (unsigned int bCount = 0; bCount < btnNameList.size(); bCount++)
	{
		theTextureMgr->addTexture(btnNameList[bCount], btnTexturesToUse[bCount]);
	}
	for (unsigned int bCount = 0; bCount < btnNameList.size(); bCount++)
	{
		cButton* newBtn = new cButton();
		newBtn->setTexture(theTextureMgr->getTexture(btnNameList[bCount]));
		newBtn->setSpritePos(btnPos[bCount]);
		newBtn->setSpriteDimensions(theTextureMgr->getTexture(btnNameList[bCount])->getTWidth(), theTextureMgr->getTexture(btnNameList[bCount])->getTHeight());
		theButtonMgr->add(btnNameList[bCount], newBtn);
	}
	theBtnType = btnTypes::exit;

	theSoundMgr->getSnd("theme")->play(-1);

	spriteBkgd.setSpritePos({ 0, 0 });
	spriteBkgd.setTexture(theTextureMgr->getTexture("theBackground"));
	spriteBkgd.setSpriteDimensions(theTextureMgr->getTexture("theBackground")->getTWidth(), theTextureMgr->getTexture("theBackground")->getTHeight());

	thePlayer.setSpritePos({ 400,600 });
	thePlayer.setTexture(theTextureMgr->getTexture("player"));
	thePlayer.setSpriteDimensions(theTextureMgr->getTexture("player")->getTWidth(), theTextureMgr->getTexture("player")->getTHeight());

	for (int atank = 0; atank < 6; atank++)
	{
		theTanks.add(theTextureMgr, textureName, { (150 * atank) + 75,40 }, 0.0f, 100, atank);
	}

	strScore = gameTextList[1];
	strScore += to_string(tanksDestroyed).c_str();
	//EndScore = strScore;

}

void cGame::run(SDL_Renderer* theRenderer)
{
	loop = true;

	while (loop)
	{
		//We get the time that passed since the last frame
		double elapsedTime = this->getElapsedSeconds();

		loop = this->getInput(loop);
		this->update(elapsedTime);
		this->render(theRenderer);
	}
}

void cGame::render(SDL_Renderer* theRenderer)
{
	SDL_RenderClear(theRenderer);
	SDL_Rect theTextureRectangle = {0,0,0,0};
	SDL_Rect theButtonDims = { 0,0,0,0 };
	SDL_Rect theButtonPos = { 0,0,0,0 };

	switch (theGameState)
	{
	case gameState::menu:
	{
		spriteBkgd.setTexture(theTextureMgr->getTexture("openingScreen"));
		spriteBkgd.setSpriteDimensions(theTextureMgr->getTexture("openingScreen")->getTWidth(), theTextureMgr->getTexture("openingScreen")->getTHeight());
		spriteBkgd.render(theRenderer, NULL, NULL, spriteBkgd.getSpriteRotAngle(), &spriteBkgd.getSpriteCentre());

		// Title text 
		tempTextTexture = theTextureMgr->getTexture("Title");
		theTextureRectangle = tempTextTexture->getTextureRect();
		pos = { 170, 100, theTextureRectangle.w*2, theTextureRectangle.h*2 };
		tempTextTexture->renderTexture(theRenderer, tempTextTexture->getTexture(), &theTextureRectangle, &pos);

		// Render Button
		theButtonMgr->getBtn("play_btn")->render(theRenderer, &theButtonMgr->getBtn("play_btn")->getSpriteDimensions(),
			&theButtonMgr->getBtn("play_btn")->getSpritePos(), theButtonMgr->getBtn("play_btn")->getSpriteRotAngle(), &theButtonMgr->getBtn("play_btn")->getSpriteCentre());
		theButtonMgr->getBtn("instructions_btn")->render(theRenderer, &theButtonMgr->getBtn("instructions_btn")->getSpriteDimensions(),
			&theButtonMgr->getBtn("instructions_btn")->getSpritePos(), theButtonMgr->getBtn("instructions_btn")->getSpriteRotAngle(),
			&theButtonMgr->getBtn("instructions_btn")->getSpriteCentre());
		theButtonMgr->getBtn("play_btn")->setSpriteDimensions(102, 50);
		theButtonMgr->getBtn("play_btn")->setSpritePos({ 450, 300 });
		theButtonMgr->getBtn("instructions_btn")->setSpriteDimensions(200, 50);
		theButtonMgr->getBtn("instructions_btn")->setSpritePos({ 400, 370 });
		theButtonMgr->getBtn("exit_btn")->setSpriteDimensions(102, 50);
		theButtonMgr->getBtn("exit_btn")->setSpritePos({ 450, 440 });
		theButtonMgr->getBtn("exit_btn")->render(theRenderer, &theButtonMgr->getBtn("exit_btn")->getSpriteDimensions(),
			&theButtonMgr->getBtn("exit_btn")->getSpritePos(), theButtonMgr->getBtn("exit_btn")->getSpriteRotAngle(), &theButtonMgr->getBtn("exit_btn")->getSpriteCentre());
	}
	break;
	case gameState::instructions:
	{
		spriteBkgd.setTexture(theTextureMgr->getTexture("instructionsScreen"));
		spriteBkgd.setSpriteDimensions(theTextureMgr->getTexture("instructionsScreen")->getTWidth(), theTextureMgr->getTexture("instructionsScreen")->getTHeight());
		spriteBkgd.render(theRenderer, NULL, NULL, spriteBkgd.getSpriteRotAngle(), &spriteBkgd.getSpriteCentre());

		//Instructions
		tempTextTexture = theTextureMgr->getTexture("instructions");
		theTextureRectangle = tempTextTexture->getTextureRect();
		pos = { 170, 200, theTextureRectangle.w , theTextureRectangle.h };
		tempTextTexture->renderTexture(theRenderer, tempTextTexture->getTexture(), &theTextureRectangle, &pos);
		//Instructions Second Line
		tempTextTexture = theTextureMgr->getTexture("instructions2");
		theTextureRectangle = tempTextTexture->getTextureRect();
		pos = { 170, 250, theTextureRectangle.w , theTextureRectangle.h };
		tempTextTexture->renderTexture(theRenderer, tempTextTexture->getTexture(), &theTextureRectangle, &pos);
		//Instructions Third Line
		tempTextTexture = theTextureMgr->getTexture("goal");
		theTextureRectangle = tempTextTexture->getTextureRect();
		pos = { 170, 300, theTextureRectangle.w , theTextureRectangle.h };
		tempTextTexture->renderTexture(theRenderer, tempTextTexture->getTexture(), &theTextureRectangle, &pos);

		theButtonMgr->getBtn("menu_btn")->setSpritePos({ 450, 400 });
		//theButtonMgr->getBtn("menu_btn")->setSpritePos({ 500, 500 });
		theButtonMgr->getBtn("menu_btn")->render(theRenderer, &theButtonMgr->getBtn("menu_btn")->getSpriteDimensions(),
			&theButtonMgr->getBtn("menu_btn")->getSpritePos(), theButtonMgr->getBtn("menu_btn")->getSpriteRotAngle(), &theButtonMgr->getBtn("menu_btn")->getSpriteCentre());
		break;
	}
	case gameState::playing:
	{
		spriteBkgd.setTexture(theTextureMgr->getTexture("theBackground"));
		spriteBkgd.setSpriteDimensions(theTextureMgr->getTexture("theBackground")->getTWidth(), theTextureMgr->getTexture("theBackground")->getTHeight());
		spriteBkgd.render(theRenderer, NULL, NULL, spriteBkgd.getSpriteRotAngle(), &spriteBkgd.getSpriteCentre());

		tempTextTexture = theTextureMgr->getTexture("TitleTxt");
		theTextureRectangle = tempTextTexture->getTextureRect();
		pos = { 10, 10, theTextureRectangle.w, theTextureRectangle.h };
		tempTextTexture->renderTexture(theRenderer, tempTextTexture->getTexture(), &theTextureRectangle, &pos);

		tempTextTexture->renderTexture(theRenderer, tempTextTexture->getTexture(), &tempTextTexture->getTextureRect(), &pos);
		theTextureMgr->addTexture("score", theFontMgr->getFont("digital")->createTextTexture(theRenderer, strScore.c_str(), textType::solid, { 255, 255, 0, 255 }, { 0, 0, 0, 0 }));
		tempTextTexture = theTextureMgr->getTexture("score");
		pos = { 600, 10, tempTextTexture->getTextureRect().w, tempTextTexture->getTextureRect().h };
		tempTextTexture->renderTexture(theRenderer, tempTextTexture->getTexture(), &tempTextTexture->getTextureRect(), &pos);

		theTanks.render(theRenderer);
		thePlayer.render(theRenderer, &thePlayer.getSpriteDimensions(), &thePlayer.getSpritePos(), thePlayer.getSpriteRotAngle(), &thePlayer.getSpriteCentre());
		theShells.render(theRenderer);
	}
	break;
	case gameState::end:
	{
		spriteBkgd.setTexture(theTextureMgr->getTexture("endScreen"));
		spriteBkgd.setSpriteDimensions(theTextureMgr->getTexture("endScreen")->getTWidth(), theTextureMgr->getTexture("endScreen")->getTHeight());
		spriteBkgd.render(theRenderer, NULL, NULL, spriteBkgd.getSpriteRotAngle(), &spriteBkgd.getSpriteCentre());

		tempTextTexture = theTextureMgr->getTexture("GameOver");
		theTextureRectangle = tempTextTexture->getTextureRect();
		pos = { 290, 200, theTextureRectangle.w*2, theTextureRectangle.h*2 };
		tempTextTexture->renderTexture(theRenderer, tempTextTexture->getTexture(), &theTextureRectangle, &pos);

		tempTextTexture->renderTexture(theRenderer, tempTextTexture->getTexture(), &tempTextTexture->getTextureRect(), &pos);
		theTextureMgr->addTexture("score2", theFontMgr->getFont("digital")->createTextTexture(theRenderer, strScore.c_str(), textType::solid, { 255, 255, 0, 255 }, { 0, 0, 0, 0 }));
		tempTextTexture = theTextureMgr->getTexture("score2");
		pos = { 290, 280, tempTextTexture->getTextureRect().w, tempTextTexture->getTextureRect().h };
		tempTextTexture->renderTexture(theRenderer, tempTextTexture->getTexture(), &tempTextTexture->getTextureRect(), &pos);



		//theButtonMgr->getBtn("menu_btn")->setSpriteDimensions(102, 50);
		theButtonMgr->getBtn("menu_btn")->setSpritePos({ 450, 330 });
		//theButtonMgr->getBtn("menu_btn")->setSpritePos({ 500, 500 });
		theButtonMgr->getBtn("menu_btn")->render(theRenderer, &theButtonMgr->getBtn("menu_btn")->getSpriteDimensions(),
			&theButtonMgr->getBtn("menu_btn")->getSpritePos(), theButtonMgr->getBtn("menu_btn")->getSpriteRotAngle(), &theButtonMgr->getBtn("menu_btn")->getSpriteCentre());

		theButtonMgr->getBtn("exit_btn")->setSpriteDimensions(102, 50);
		theButtonMgr->getBtn("exit_btn")->setSpritePos({ 450, 440 });
		theButtonMgr->getBtn("exit_btn")->render(theRenderer, &theButtonMgr->getBtn("exit_btn")->getSpriteDimensions(),
			&theButtonMgr->getBtn("exit_btn")->getSpritePos(), theButtonMgr->getBtn("exit_btn")->getSpriteRotAngle(), &theButtonMgr->getBtn("exit_btn")->getSpriteCentre());
	}
	break;
	case gameState::quit:
	{
		loop = false;
	}
	break;
	default:
		break;
	}

	SDL_RenderPresent(theRenderer);
}

void cGame::update()
{
}

void cGame::update(double theDeltaTime)
{
	switch (theGameState)
	{
	case gameState::menu:
	{
		theGameState = theButtonMgr->getBtn("exit_btn")->update(theGameState, gameState::quit, theAreaClicked);
		theGameState = theButtonMgr->getBtn("play_btn")->update(theGameState, gameState::playing, theAreaClicked);
		theGameState = theButtonMgr->getBtn("instructions_btn")->update(theGameState, gameState::instructions, theAreaClicked);
	}
	break;
	case gameState::playing:
	{
		theTanks.update(theDeltaTime);
		//thePlayer.update(theDeltaTime, "leftRight");
		theShells.update(theDeltaTime);
		theTanks.theNumActiveTanks();
		for (int atank = 0; atank < theTanks.theNumTanks(); atank++)
		{
			for (int aShell = 0; aShell < theShells.theNumShells(); aShell++)
			{
				theShells.checkCollisions(&theTanks.getTankBoundingRect(atank));
				theTanks.checkCollisions(&theShells.getShellBoundingRect(aShell));
			}
		}
		

		if (tanksDestroyed < theTanks.getTanksDestroyed())
		{
			//Create Updated score
			tanksDestroyed = theTanks.getTanksDestroyed();
			strScore = gameTextList[1];
			strScore += to_string(tanksDestroyed).c_str();
			theTextureMgr->deleteTexture("score");
		}
		if (theTanks.theNumActiveTanks() == 0 || tanksDestroyed == 6)
		{
			//End game
			gameOver = true;
		}

		if (gameOver)
		{
			theGameState = gameState::end;
		}
		
	}
	break;
	case gameState::end:
	{
		theGameState = theButtonMgr->getBtn("menu_btn")->update(theGameState, gameState::menu, theAreaClicked);
		theGameState = theButtonMgr->getBtn("exit_btn")->update(theGameState, gameState::quit, theAreaClicked);

	}
	break;
	case gameState::instructions:
	{
		theGameState = theButtonMgr->getBtn("menu_btn")->update(theGameState, gameState::menu, theAreaClicked);
		
	}
	break;
	case gameState::quit:
	{
		loop = false;
	}
	break;
	default:
		break;
	}

}

bool cGame::getInput(bool theLoop)
{
	SDL_Event event;

	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT)
		{
			theLoop = false;
		}

		switch (event.type)
		{
			case SDL_MOUSEBUTTONDOWN:
				switch (event.button.button)
				{
				case SDL_BUTTON_LEFT:
				{
					//theSoundMgr->getSnd("click")->play(0);				
					theAreaClicked = { event.motion.x, event.motion.y };
					
				}
				break;
				case SDL_BUTTON_RIGHT:
					break;
				default:
					break;
				}
				break;
			case SDL_MOUSEBUTTONUP:
				switch (event.button.button)
				{
				case SDL_BUTTON_LEFT:
				{
				}
				break;
				case SDL_BUTTON_RIGHT:
					break;
				default:
					break;
				}
				break;
			case SDL_MOUSEMOTION:
			{
			}
			break;
			case SDL_KEYDOWN:
				
				switch (event.key.keysym.sym)
				{
				case SDLK_ESCAPE:
					theLoop = false;
					break;
				case SDLK_DOWN:
				{
					
				}
				break;

				case SDLK_RIGHT:
				{
					
					//thePlayer.setTankVelocity(100);
				}
				break;

				case SDLK_LEFT:
				{
					
					//thePlayer.setTankVelocity(-100);
				}
				break;
				case SDLK_UP:
				{
					
				}
				break;
				case SDLK_d:
				{
					thePlayer.setSpritePos({ thePlayer.getSpritePos().x + 20, thePlayer.getSpritePos().y });
				}
				break;

				case SDLK_a:
				{
					thePlayer.setSpritePos({ thePlayer.getSpritePos().x - 20, thePlayer.getSpritePos().y });
				}
				break;
				case SDLK_w:
				{
					thePlayer.setSpritePos({ thePlayer.getSpritePos().x , thePlayer.getSpritePos().y - 20 });
				}
				break;

				case SDLK_s:
				{
					thePlayer.setSpritePos({ thePlayer.getSpritePos().x , thePlayer.getSpritePos().y + 20 });
				}
				break;

				case SDLK_SPACE:
				{
					int numShells = theShells.theNumShells();
					SDL_Point tankPos = {thePlayer.getSpritePos().x, thePlayer.getSpritePos().y };
					theSoundMgr->getSnd("fire")->play(0);
					theShells.add(theTextureMgr, textureName, tankPos, thePlayer.getTankRotation(), 1000, numShells);
					
				}
				break;
				default:
					break;
				}
			case SDL_TEXTINPUT:
			{
				//cin.clear();
			//	if (event.key.keysym.sym == SDLK_BACKSPACE && userName.length() > 0)
			//	{
			//		// Remove last character
			//		userName.pop_back();
			//		renderText = true;
			//		cout << userName << endl;
			//	}
			//	else if (event.key.keysym.sym == SDLK_RETURN && userName.size() != 0)
			//	{
			//		//inputCmd = inputText.c_str();
			//		renderText = true;
			//		//inputText = "";
			//	}
			//	else
			//	{
			//		userName += (char)(event.key.keysym.sym); //event.text.text[0];
			//		renderText = true;
			//	}
			//	
			//	cout << userName << endl;
			}
			break;
			case SDL_TEXTEDITING:
			{

			}
			break;
			default:
				break;
		}

	}
	return theLoop;
}

double cGame::getElapsedSeconds()
{
	this->m_CurrentTime = high_resolution_clock::now();
	this->deltaTime = (this->m_CurrentTime - this->m_lastTime);
	this->m_lastTime = this->m_CurrentTime;
	return deltaTime.count();
}

void cGame::cleanUp(SDL_Window* theSDLWND)
{

	// Delete our OpengL context
	SDL_GL_DeleteContext(theSDLWND);

	// Destroy the window
	SDL_DestroyWindow(theSDLWND);

	//Quit FONT system
	TTF_Quit();

	// Quit IMG system
	IMG_Quit();

	// Shutdown SDL 2
	SDL_Quit();
}

