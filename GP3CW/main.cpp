#define WIN32_LEAN_AND_MEAN
#define WIN32_EXTRA_LEAN

#define GLX_GLXEXT_LEGACY //Must be declared so that our local glxext.h is picked up, rather than the system one


#include "GameConstants.h"
#include <windows.h>
#include "windowOGL.h"
#include "cWNDManager.h"
#include "cModel.h"
#include "cModelLoader.h"
#include "cFont.h"
#include "cSound.h"
#include <libdrawtext-0.2.1\drawtext.h>
#include <time.h>



int WINAPI WinMain(HINSTANCE hInstance,
                   HINSTANCE hPrevInstance,
                   LPSTR cmdLine,
                   int cmdShow)
{

    //Set our window settings
    const int windowWidth = 1024;
    const int windowHeight = 768;
    const int windowBPP = 16;



    //This is our window
	static cWNDManager* pgmWNDMgr = cWNDManager::getInstance();

    //The example OpenGL code
    windowOGL theOGLWnd;

    //Attach our example to our window
	pgmWNDMgr->attachOGLWnd(&theOGLWnd);


    //Attempt to create the window
	if (!pgmWNDMgr->createWND(windowWidth, windowHeight, windowBPP))
    {
        //If it fails

        MessageBox(NULL, "Unable to create the OpenGL Window", "An error occurred", MB_ICONERROR | MB_OK);
		pgmWNDMgr->destroyWND(); //Reset the display and exit
        return 1;
    }

	if (!theOGLWnd.initOGL()) //Initialize our example
    {
        MessageBox(NULL, "Could not initialize the application", "An error occurred", MB_ICONERROR | MB_OK);
		pgmWNDMgr->destroyWND(); //Reset the display and exit
        return 1;
    }

	

	srand(time(NULL));
	glm::vec3 mdlPos;

	float mdlVelocity = 0.0f;
	float posInc = 0.0f;
	float posY = 45.0f;
	const int numUFO = 30;

	// Aliens Loader
	cModelLoader alienModel;
	alienModel.initialise("Models/alienModel.obj");
	cModelLoader alienModel1;
	alienModel1.initialise("Models/alienModel2.obj");
	cModelLoader alienModel2;
	alienModel2.initialise("Models/alienModel3.obj");
	int modelType = 0;

	vector <cModel*> alienList;
	vector <cModel*>::iterator alienIndex;

	for (int loop = 0; loop < numUFO; loop++)
	{
		if ((loop % (numUFO / 3)) == 0)
		{
			posInc = 0.0f;
			posY += -10.0f;
			modelType += 1;
		}
		else
		{
			posInc += 5.0f;
		}
		
		cModel* aAlien = new cModel();

		mdlPos.x = -36.0f + posInc; 
		mdlPos.y = posY;
		mdlPos.z = 0.0f;
	
		aAlien->setPosition(mdlPos);
		aAlien->setRotation(0.0f);
		aAlien->setModelType(1);
		aAlien->setVelocity(glm::vec3(0.0f, 0.0f, mdlVelocity));
		switch (modelType){
		case 1:{
			aAlien->setMdlDimensions(alienModel.getModelDimensions()); 
			aAlien->setIsAlienType(1);
			break;
			}
		case 2:{
			aAlien->setMdlDimensions(alienModel1.getModelDimensions()); 
			aAlien->setIsAlienType(2);
			break;
			}
		case 3:	{
			aAlien->setMdlDimensions(alienModel2.getModelDimensions()); 
			aAlien->setIsAlienType(3);
			break;
			}
		}

		aAlien->setIsActive(true);

		alienList.push_back(aAlien);
	}

	// Load Player

	cModelLoader playerMdl;
	playerMdl.initialise("Models/Drone.obj");

	cModel playerMod;
	mdlPos.x = 0.0f;
	mdlPos.y = -35.0f;
	mdlPos.z = 0.0f;
	playerMod.initialise(mdlPos, 90.0f, glm::vec3(0.0f, 0.0f, mdlVelocity), 2, true);
	playerMod.setRotation(180.0f);

	//Prepare Missiles
	cModelLoader missilModel;
	missilModel.initialise("Models/missileModel.obj");
	int numMissiles = 0;
	vector < cModel* > missileList;
	vector < cModel* >::iterator index;
	
	//load audio
	cSound firingFX;
	firingFX.createContext();
	firingFX.loadWAVFile("Audio/shot007.wav");
	
	cSound explosionFX;
	explosionFX.loadWAVFile("Audio/explosion2.wav");
	
	cSound themeMusic;
	themeMusic.loadWAVFile("Audio/spaceinvaders.wav");
	themeMusic.playAudio(AL_LOOPING);
	bool isPlaying = true;

	// Load font
	struct dtx_font	*fntmain;
	fntmain = dtx_open_font("Fonts/Kahlesv2.ttf", 0);
	dtx_prepare_range(fntmain,20, 0, 256);
	
	/* ASCII */
	dtx_use_font(fntmain,20);
	int playerScore = 0;

	
	
	


    //This is the mainloop, we render frames until isRunning returns false
	while (pgmWNDMgr->isWNDRunning())
    {
		pgmWNDMgr->processWNDEvents(); //Process any window events

        //We get the time that passed since the last frame
		float elapsedTime = pgmWNDMgr->getElapsedSeconds();
		
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		theOGLWnd.initOGL();
		glClearColor(0, 0.25, 1, 1);
		
		if (!isSoundOn){
			themeMusic.stopAudio();
			isPlaying = false;
		}
		else if (isPlaying == false && isSoundOn)
		{
			themeMusic.playAudio(AL_LOOPING);
			isPlaying = true;
		}


		
		playerMod.getPosition();
		float x, y, z;
		x = y = z = 0.0f;
		x += playerMod.getPosition().x;
		y += playerMod.getPosition().y;
		z += playerMod.getPosition().z;
		
		if (!is3rdPerson)
			gluLookAt(0, 0, 100, 0, 0, 0, 0, 1, 0);
		else
			gluLookAt(x , y-5.0f , z+2.0f, x, y+5, 0 , 0 , 0 , 1);

		glPushMatrix();

		
		playerMod.getPosition();
		//float x, y, z;
		x = y = z = 0.0f;
		x += playerMod.getPosition().x;
		y += playerMod.getPosition().y;
		z += playerMod.getPosition().z;
		glTranslatef(x, y, z);
		glRotated(90.0f, 1.0f, 0.0f, 0.0f);
		glTranslatef(-x, -y, -z);
		playerMdl.renderMdl(playerMod.getPosition());
		playerMod.update(elapsedTime);

		


	
		for (alienIndex = alienList.begin(); alienIndex != alienList.end(); ++alienIndex)
		{
			glm::vec3 mdlPosition = (*alienIndex)->getPosition();
			switch ((*alienIndex)->isAlienType())
			{
			case 1: 
				alienModel.renderMdl((*alienIndex)->getPosition());
				break;
			case 2 : 
				alienModel1.renderMdl((*alienIndex)->getPosition());
				break;
			case 3 : 
				alienModel2.renderMdl((*alienIndex)->getPosition());
				break;
			}

			(*alienIndex)->update(elapsedTime);

			if (mdlPosition.x >= 36.0f){ directionUFO = false; }
			else if (mdlPosition.x <= -36.0f){ directionUFO = true; }
		}
		

		
		while (isFiring)
		{
			cModel* missile = new cModel();
			glm::vec3 missileDirection =  glm::vec3(0.0f,3.0f,0.0f);

			missile->setPosition(playerMod.getPosition() + missileDirection);
			missile->setRotation(0.0f);
			missile->setModelType(3);
			missile->setVelocity(glm::vec3(0.0f, 0.0f, mdlVelocity));
			missile->setMdlDimensions(missilModel.getModelDimensions());
			missile->setIsActive(true);
			missile->update(elapsedTime);
			missileList.push_back(missile);
			isFiring = false;
			if (isSoundOn)
				firingFX.playAudio(AL_FALSE);
		}
		
		for (index = missileList.begin(); index != missileList.end(); ++index)
		{
			missilModel.renderMdl((*index)->getPosition());
			(*index)->update(elapsedTime);

			for (alienIndex = alienList.begin(); alienIndex != alienList.end(); ++alienIndex)
			{
				if ((*index)->SphereSphereCollision((*alienIndex)->getPosition(), (*alienIndex)->getMdlRadius()))
				{
					(*index)->setIsActive(false);
					(*alienIndex)->setIsActive(false);
					playerScore += 100;
					if (isSoundOn)
						explosionFX.playAudio(AL_FALSE);
					break;
				}
			
			}

		}
		
	
		// clear the missiles out of screen or hit alien formm the vectors
		index = missileList.begin();
		while (index != missileList.end())
		{
			if ((*index)->getPosition().y > 50 || (*index)->isActive() == false)
			{
				index = missileList.erase(index);
			}
			else
			{
				++index;
			}
		}
		// clear the aliens that have been hit by a missile 
		alienIndex = alienList.begin();
		while (alienIndex != alienList.end())
		{
			if ((*alienIndex)->isActive() == false)
			{
				alienIndex = alienList.erase(alienIndex);
			}
			else
			{
				++alienIndex;
			}
		}
	
		
		
		glMatrixMode(GL_PROJECTION);
		glPushMatrix();
		glLoadIdentity();
		gluOrtho2D(0, windowWidth, 0, windowHeight);
		glMatrixMode(GL_MODELVIEW);
		
		glPushMatrix();
		glLoadIdentity();
		glPushAttrib(GL_DEPTH_TEST);
		glDisable(GL_DEPTH_TEST	);
		
		glTranslatef(10, 20, 0);

		string scoreString = "Score : " + to_string(static_cast<long long> (playerScore));
		//display the score
		dtx_string(scoreString.c_str());


		glMatrixMode(GL_PROJECTION);
		glPopMatrix();
		glMatrixMode(GL_MODELVIEW);
		glPopMatrix();
		
		pgmWNDMgr->swapBuffers();
    }

	theOGLWnd.shutdown(); //Free any resources
	pgmWNDMgr->destroyWND(); //Destroy the program window

    return 0; //Return success
}
