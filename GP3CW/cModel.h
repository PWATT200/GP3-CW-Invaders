#ifndef _CMODEL_H
#define _CMODEL_H

#include "GameConstants.h"

class cModel
{
public:
	cModel();
	void setPosition(glm::vec3 mdlPosition);
	void setRotation(GLfloat mdlRotation);
	void setVelocity(glm::vec3 mdlVelocity);
	void setModelType(int isModel);
	void setMdlDimensions(mdlDimensions mdlDims);
	void setMdlRadius(float mdlRadius);
	void setIsActive(bool mdlIsActive);
	void setIsAlienType(int mdlIsAlienType);

	glm::vec3 getPosition();
	GLfloat getRotation();
	glm::vec3 getVelocity();
	int getModelType();
	mdlDimensions getMdlDimensions();
	float getMdlRadius();
	bool isActive();
	int isAlienType();
	

	void initialise(glm::vec3 mdlPosition, GLfloat mdlRotation, glm::vec3 mdlVelocity, int isModel, bool mdlIsActive);
	void update(float elapsedTime);

	bool SphereSphereCollision(glm::vec3 mdlPosition, float mdlRadius);


	~cModel();
private:
	// Set the position of the model in world space, and set the rotation.
	glm::vec3 m_mdlPosition = glm::vec3(0.0f,0.0f,0.0f);
	GLfloat m_mdlRotation = 0.0f;
	glm::vec3 m_mdlVelocity = glm::vec3(0.0f, 0.0f, 0.0f);
	mdlDimensions m_Dimensions;

	int m_isModel = 0;
	float lengthSQRD(glm::vec3 mdlLength);
	float m_mdlRadius;
	bool m_IsActive;
	int m_IsAlienType;
};
#endif
