#include "Draw.h"
#include <Windows.h>
//функция отрисовки текстур
void drawTexture(GLuint texture, int x, int y, int x1, int y1) {
	glColor3f(1, 1, 1);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glEnable(GL_TEXTURE_2D);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glBindTexture(GL_TEXTURE_2D, texture);
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 1); glVertex2f(x, y1);
	glTexCoord2f(1, 1); glVertex2f(x1, y1);
	glTexCoord2f(1, 0); glVertex2f(x1, y);
	glTexCoord2f(0, 0); glVertex2f(x, y);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);
}

void centerOnScreen(int width, int height) {
	//центрируем окно на экране
	RECT desktop;
	const HWND hDesktop = GetDesktopWindow();
	GetWindowRect(hDesktop, &desktop);
	glutPositionWindow((desktop.right - width) / 2, (desktop.bottom - height) / 2);
}