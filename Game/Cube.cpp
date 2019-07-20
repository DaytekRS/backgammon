#include "Game.h"
using namespace Game;
//инициализация кубика
Cube::Cube() {
	one= SOIL_load_OGL_texture("img/cube/1.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);
	two = SOIL_load_OGL_texture("img/cube/2.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);
	three = SOIL_load_OGL_texture("img/cube/3.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);
	four = SOIL_load_OGL_texture("img/cube/4.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);
	five = SOIL_load_OGL_texture("img/cube/5.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);
	six = SOIL_load_OGL_texture("img/cube/6.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);
	cast(); //выполнение броска
}
void Cube::setLocation(int x,int y) {
	this->x = x;
	this->y = y;
}
void Cube::setSize(int width, int heigth) {
	this->width = width;
	this->height = heigth;
}
//выполнение броска
void Cube::cast() {
	haveDouble = false;
	stateOne = 1 + rand() % 6;
	stateTwo = 1 + rand() % 6;
	if (stateOne == stateTwo) haveDouble = true;
}
bool Cube::getHaveDouble() {
	return haveDouble;
}
void Cube::setHaveDouble(bool set) {
	haveDouble=set;
}
void Cube::draw() {
	//рисуем первый кубик
	switch (stateOne)
	{
	case 1:
		drawTexture(one, x, y, x + width, y + height);
		break;
	case 2:
		drawTexture(two, x, y, x + width, y + height);
		break;
	case 3:
		drawTexture(three, x, y, x + width, y + height);
		break;
	case 4:
		drawTexture(four, x, y, x + width, y + height);
		break;
	case 5:
		drawTexture(five, x, y, x + width, y + height);
		break;
	case 6:
		drawTexture(six, x, y, x + width, y + height);
		break;
	}
	//рисуем второй кубик
	switch (stateTwo)
	{
	case 1:
		drawTexture(one, x+ width+ space, y, x + 2*width+ space, y + height);
		break;
	case 2:
		drawTexture(two, x + width + space, y, x + 2 * width + space, y + height);
		break;
	case 3:
		drawTexture(three, x + width + space, y, x + 2 * width + space, y + height);
		break;
	case 4:
		drawTexture(four, x + width + space, y, x + 2 * width + space, y + height);
		break;
	case 5:
		drawTexture(five, x + width + space, y, x + 2 * width + space, y + height);
		break;
	case 6:
		drawTexture(six, x + width + space, y, x + 2 * width + space, y + height);
		break;
	}
}

void Cube::setSpace(int space) {
	this->space = space;
}
int Cube::getStateOne() {
	return stateOne;
}
int Cube::getStateTwo() {
	return stateTwo;
}

void Cube::setState(int stateOne,int stateTwo) {
	this->stateOne = stateOne;
	this->stateTwo = stateTwo;
}