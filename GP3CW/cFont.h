/*
==========================================================================
cFont.h
==========================================================================
*/

#ifndef _FONT_H
#define _FONT_H

// OpenGL Headers
#include <windows.h>
#include <GL\glut.h>
#include <string>
#include <stdio.h>

using namespace std;

class cFont
{
public:

	cFont();

	~cFont();

	void initFont(HDC hDevContext, LPCSTR sFile);
	HFONT createFont(LPCSTR sFile);
	void renderText(LPCSTR string);

private:
	HFONT m_fontToUse;
	HDC m_hDC;
	GLuint m_textList;
	HANDLE m_HFontHdle;
};
#endif