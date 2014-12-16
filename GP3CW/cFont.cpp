/*
==========================================================================
cFont.cpp
==========================================================================
*/

#include "cFont.h"
using namespace std;
/*
=================================================================================
Constructor
=================================================================================
*/

cFont::cFont()
{

	m_fontToUse = NULL;
}

/*
=================
- Destructor.
=================
*/
cFont::~cFont()					// Destructor
{
	if (m_fontToUse != NULL)
		m_fontToUse = NULL;
	RemoveFontMemResourceEx(m_HFontHdle);
}

void cFont::initFont(HDC hDevContext, LPCSTR sFile)
{
	m_hDC = hDevContext;

	//Create 128 empty display lists
	m_textList = glGenLists(128);
	m_fontToUse = createFont(sFile);

	//Set the device context to use the newly created font
	SelectObject(m_hDC, m_fontToUse);

	//Create 128 bitmap display lists in the textLists
	wglUseFontBitmaps(m_hDC, 0, 128, m_textList);

}

HFONT cFont::createFont(LPCSTR sFile)
{
	//Create a font with the given parameters
	m_fontToUse = CreateFont(32,						//Height of the font
		18,						//Use the default width
		0,						//Angle of each character
		0,						//Orientation
		FW_NORMAL,				//Weight of the font
		FALSE,					//Do not use italics
		FALSE,					//Do not underline
		FALSE,					//Do not strikeout
		ANSI_CHARSET,				//Use ansi characters
		OUT_TT_PRECIS,			//Try to use truetype fonts
		CLIP_DEFAULT_PRECIS,		//Default clipping precision
		ANTIALIASED_QUALITY,		//Antialias the font
		FF_DONTCARE | DEFAULT_PITCH,// Family And Pitch
		sFile);				//Use the font specified by sFile

	if (m_fontToUse == NULL)
	{
		return NULL;
	}
	else
	{
		return m_fontToUse;
	}
}


void cFont::renderText(LPCSTR stringToRender)
{
	//Prepare to use the projection matrix
	glMatrixMode(GL_PROJECTION);

	//Set the projection matrix to an identity matrix
	glLoadIdentity();

	//Create an orthographic projection matrix (because we're going to be drawing the text in 2D)
	glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);

	//Prepare to use the Model-View matrix
	glMatrixMode(GL_MODELVIEW);

	//Use the identity modelview matrix
	glLoadIdentity();

	//Prepare to draw in the top left corner of the screen
	glRasterPos2f(-0.9f, 0.8f);

	//Create and initialise a 128 character string
	char pTextBuffer[128];
	memset(pTextBuffer, '\0', sizeof(char) * 128);

	//Copy text into the string
	sprintf_s(pTextBuffer, 128, stringToRender);

	//Prepare to draw the display lists contained in m_textList onwards
	glListBase(m_textList);

	//Draw the text display lists
	glCallLists(strlen(pTextBuffer), GL_UNSIGNED_BYTE, pTextBuffer);

}