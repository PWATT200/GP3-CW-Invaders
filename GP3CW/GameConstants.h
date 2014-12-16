#ifndef _GAMECONSTANTS_H
#define _GAMECONSTANTS_H

#define GLM_FORCE_RADIANS

#include <stdlib.h>
#include <Windows.h>
#include <GL\glut.h>
//#include <assimp\Importer.hpp>    // C++ importer interface
//#include <assimp\scene.h>           // Output data structure
//#include <assimp\postprocess.h>     // Post processing flags
#include <OpenAL\al.h>
#include <OpenAL\alc.h>
#include <OpenAL\alut.h>
#include "glm\glm.hpp"
#include "glm\gtc\matrix_transform.hpp"
#include "glm\geometric.hpp"
#include "glm\gtc\quaternion.hpp"
#include "glm\gtc\type_ptr.hpp"
#include "glm\gtx\quaternion.hpp"
#include "glm-0.3.2\glm\glm.h"
#include <vector>


//Define the string to appear in the top left corner of the window
#define WINDOW_TITLE "Space Invader PWATT200"

extern int drawMode;
extern float rotationAngle;
extern float translationZ;
extern bool directionUFO;
extern float playerMove;
extern bool isFiring;
extern bool is3rdPerson;
extern bool isFoged;
extern bool isSoundOn;


extern GLfloat fogColor[4];

struct mdlDimensions{
	float s_mdlWidth, s_mdlheight, s_mdldepth;
};

#endif