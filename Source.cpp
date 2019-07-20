#include <iostream>
#include <Windows.h>
#include "Controllers\Controllers.h"
#include "Menu\Menu.h"
#include "gl\glut.h"
#include "Soil\SOIL.h"
#include "Draw\Draw.h"
#include "Game\Game.h"
#include "lib/audiere.h"
#include<ctime>
#define WIDTH 540 //������� ����
#define HEIGHT  540
#define MAIN 1
#define COMPUTER 2
#define FOR_TWO 3
#define LOAD 0
#define WIN_WHITE 4
#define WIN_BLACK 5
#define LOAD_FORTWO 6
#define LOAD_COMPUTER 7
using namespace std;
using namespace Controllers;
using namespace Menu;
using namespace Game;
using namespace audiere;
AudioDevicePtr device; // ���������� ��� ��������������� �����
OutputStreamPtr sound; //
GLuint load,winBlack,winWhite;//��������
int stateGame; //������� ��������� ����
MainMenu* menu; //����� ����
GameForTwo* gameForTwo; //����� ��� ���� �� �����
GameComputer* gameComputer; //����� ��� ���� � �����������
void timer(int value) {
	glutPostRedisplay(); //  �������� ����
	glutTimerFunc(1, timer, 0);
}
void initialize() {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, WIDTH, 0, HEIGHT, -1, 1);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}
//���������� ������� ������ �� ����
void mouse(int button, int state, int ax, int ay) {
	switch (stateGame)
	{
	case(MAIN):
		menu->mouse(button, state,ax,ay,&stateGame);
		break;
	case(FOR_TWO):
		gameForTwo->mouse(button, state, ax, ay, &stateGame);
		break;
	case(COMPUTER):
		gameComputer->mouse(button, state, ax, ay, &stateGame);
		break;
	case(WIN_BLACK):
	case(WIN_WHITE):
		if (button == GLUT_LEFT_BUTTON) stateGame = LOAD;
		break;
	case(LOAD_FORTWO):
		if (gameForTwo != NULL) delete gameForTwo;
		gameForTwo = new GameForTwo(&stateGame);
		gameForTwo->load();
		stateGame = FOR_TWO;
		break;
	case (LOAD_COMPUTER):
		if (gameForTwo != NULL) delete gameForTwo;
		gameComputer = new GameComputer(&stateGame);
		gameComputer->load();
		stateGame = COMPUTER;
		break;
	default:
		break;
	}
}
//������������� ����� ����
void newGame() {
	if (menu==NULL) menu = new MainMenu(load, WIDTH, HEIGHT);
	if (gameForTwo != NULL) delete gameForTwo;
	gameForTwo = new GameForTwo(&stateGame);
	if (gameComputer != NULL) delete gameComputer;
	gameComputer = new GameComputer(&stateGame);
	if (sound == NULL) {
		device = OpenDevice();
		sound = OpenSound(device, "music.mp3", false);
		sound->setRepeat(true);
		sound->play();
	}
}
//��������� ������ ����
void draw() {
	glClearColor(0.83, 0.83, 0.83, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	switch (stateGame)
	{
	case (LOAD):
		initialize();
		drawTexture(load, 0, 0, WIDTH, HEIGHT);
		glutSwapBuffers();
		newGame();
		stateGame = MAIN;

		break;
	case(MAIN):
		menu->draw();
		break;
	case(COMPUTER):
		gameComputer->draw();
		break;
	case(FOR_TWO):
		gameForTwo->draw();
		break;
	case(WIN_WHITE):
		drawTexture(winWhite, 0, 0, WIDTH, HEIGHT);
		break;
	case(WIN_BLACK):
		drawTexture(winBlack, 0, 0, WIDTH, HEIGHT);
		break;
	}

	glutSwapBuffers();
}

//������ ���������
void main(int argc, char** argv) {
	
	
	srand(time(0)); // ��� ����� ������ ��� ����� ���������
	stateGame = LOAD; //������ ��������� ���� � ��������� ��������
	glutInit(&argc, argv);
	glutInitWindowSize(WIDTH, HEIGHT);
	RECT desktop;
	const HWND hDesktop = GetDesktopWindow();
	GetWindowRect(hDesktop, &desktop);
	glutInitWindowPosition((desktop.right - WIDTH) / 2, (desktop.bottom - HEIGHT) / 2);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutCreateWindow("�����");
	initialize();
	glutDisplayFunc(draw);
	//�������� �������
	winWhite  = SOIL_load_OGL_texture("img/winWhite.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);
	winBlack = SOIL_load_OGL_texture("img/winBlack.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);
	load = SOIL_load_OGL_texture("img/load.jpg", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);
	
	glutMouseFunc(mouse);
	glutTimerFunc(1, timer, 0);

	glutMainLoop();
	
}