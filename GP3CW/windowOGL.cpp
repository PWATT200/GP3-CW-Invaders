#include "windowOGL.h"
#include "GameConstants.h"

windowOGL::windowOGL()
{

}

bool windowOGL::initOGL()
{
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glEnable(GL_DEPTH_TEST);
	glClearStencil(0);                          // clear stencil buffer
	glClearDepth(1.0f);                         // 0 is near, 1 is far
	glDepthFunc(GL_LEQUAL);
	//glEnable(GL_TEXTURE_2D); //enable 2D texturing
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	
	GLfloat lightpos[] = { .5, 1., 1., 0. };
	glLightfv(GL_LIGHT0, GL_POSITION, lightpos);
	onResize(1024, 768);
	
	if (isFoged){
		//Fog 
		glEnable(GL_FOG);
		glFogfv(GL_FOG_COLOR, fogColor);
		glFogi(GL_FOG_MODE, GL_LINEAR);
		glFogf(GL_FOG_DENSITY, 0.35f);
		glFogf(GL_FOG_START, 1.0f);
		glFogf(GL_FOG_END, 500.0f);
	}
	else {
		glDisable(GL_FOG);
	}
    //Return success
    return true;
}

void windowOGL::renderOGL(float rotAngle)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

}

void windowOGL::shutdown()
{

}

void windowOGL::onResize(int width, int height)
{
    glViewport(0, 0, width, height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluPerspective(45.0f, float(width) / float(height), 1.0f, 100.0f);

    glMatrixMode(GL_MODELVIEW);

    glLoadIdentity();
}

