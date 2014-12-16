#include "cModelLoader.h"

cModelLoader::cModelLoader()
{
	m_model = NULL;
}


void cModelLoader::initialise(const char* mdlFilename)
{
	m_model = glmReadOBJ(mdlFilename);
	glmVertexNormals(m_model, 180.0, false);
}

void cModelLoader::renderMdl(glm::vec3 mdlPosition)
{
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	//glLoadIdentity();
	//transformations here...
	glTranslatef(mdlPosition.x, mdlPosition.y, mdlPosition.z);

	glRotatef(rotationAngle, 0, 1, 0);
 	glmDraw(m_model, GLM_SMOOTH | GLM_TEXTURE | GLM_MATERIAL);
	// Render Text
	glPopMatrix();
	//glMatrixMode(GL_MODELVIEW);
	
}

mdlDimensions cModelLoader::getModelDimensions()
{
	mdlDimensions mdl_Dims;
	GLfloat mdlDims[3];
	glmDimensions(m_model, mdlDims);
	mdl_Dims.s_mdlWidth = mdlDims[0];
	mdl_Dims.s_mdlheight = mdlDims[1];
	mdl_Dims.s_mdldepth = mdlDims[2];
	return mdl_Dims;
}

cModelLoader::~cModelLoader()
{

}
