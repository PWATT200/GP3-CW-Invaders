#include "cModel.h"

cModel::cModel()
{
	m_mdlPosition = glm::vec3(0.0f, 0.0f, 0.0f);
	m_mdlRotation = 0.0f;
	m_mdlVelocity = glm::vec3(0.0f, 0.0f, 0.0f);
	m_IsActive = false;
	m_IsAlienType = 0;
}

/// Setters 

void cModel::setPosition(glm::vec3 mdlPosition)
{
	m_mdlPosition = mdlPosition;
}

void cModel::setRotation(GLfloat mdlRotation)
{
	m_mdlRotation = mdlRotation;
}

void cModel::setVelocity(glm::vec3 mdlVelocity)
{
	m_mdlVelocity = mdlVelocity;
}

void cModel::setModelType(int isModel)
{
	m_isModel = isModel;
}

void cModel::setIsActive(bool mdlIsActive)
{
	m_IsActive = mdlIsActive;
}

void cModel::setIsAlienType(int mdlIsAlienType)
{
	m_IsAlienType = mdlIsAlienType;
}


void cModel::setMdlDimensions(mdlDimensions mdlDims)
{
	m_Dimensions = mdlDims;
	m_mdlRadius = m_Dimensions.s_mdldepth / 2;
}

void cModel::setMdlRadius(float mdlRadius)
{
	m_mdlRadius = mdlRadius;
}

//// Getters

glm::vec3 cModel::getPosition()
{
	return m_mdlPosition;
}

GLfloat cModel::getRotation()
{
	return m_mdlRotation;
}

glm::vec3 cModel::getVelocity()
{
	return m_mdlVelocity;
}

int cModel::getModelType()
{
	return m_isModel;
}

bool cModel::isActive()
{
	return m_IsActive;
}

int cModel::isAlienType()
{
	return m_IsAlienType;
}



mdlDimensions cModel::getMdlDimensions()
{
	return m_Dimensions;
}

float cModel::getMdlRadius()
{
	return m_mdlRadius;
}

void cModel::initialise(glm::vec3 mdlPosition, GLfloat mdlRotation, glm::vec3 mdlVelocity, int isModel, bool mdlIsActive)
{
	setPosition(mdlPosition);
	setRotation(mdlRotation);
	setVelocity(mdlVelocity);
	setIsActive(mdlIsActive);
	setModelType(isModel);
	glm::vec3 mdlPos = getPosition();
	GLfloat mdlRot = getRotation();

	glRotatef(mdlRot, 1.0f, 0.0f, 0.0f);
	glTranslatef(mdlPos.x,mdlPos.y,mdlPos.z);

	

}

void cModel::update(float elapsedTime)
{
	
	float moveX = 0.0f;
	float moveY = 0.0f;
	
	switch (m_isModel)
	{
	case 1:
	{
		if (directionUFO){ moveX = 4.0f; }
		else { moveX = -4.0f; }
		moveY = -0.1f;
	}
		break;
	case 2:
	{
		moveX = playerMove;
		
	}
		break;
	case 3:
	{
		moveY = 10.0f;
	}
		break;
	}
	m_mdlPosition += glm::vec3(moveX * elapsedTime, moveY * elapsedTime, 0.0f);
}

bool cModel::SphereSphereCollision(glm::vec3 mdlPosition, float mdlRadius)
{
	const float distSq = lengthSQRD(m_mdlPosition - mdlPosition);

	const float sumRadius = (m_mdlRadius + mdlRadius);

	if (distSq < sumRadius * sumRadius)
	{
		return true; // Collision
	}
	return false; // No Collision
}

float cModel::lengthSQRD(glm::vec3 mdlLength)
{
	return (mdlLength.x * mdlLength.x) + (mdlLength.y * mdlLength.y) + (mdlLength.z * mdlLength.z);
}


cModel::~cModel()
{

}
