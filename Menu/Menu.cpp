#include "Menu.h"
#include "../Draw/Draw.h"

void Menu::MainMenu::draw() {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, WIDTH, 0, HEIGHT, -1, 1);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glutReshapeWindow(WIDTH, HEIGHT);
	centerOnScreen(WIDTH, HEIGHT);
	
	drawTexture(fon, 0, 0, WIDTH, HEIGHT);
	withComputer->draw();
	forTwo->draw();
	load->draw();
	close->draw();
}
Menu::MainMenu::MainMenu(GLuint load, int WIDTH,int HEIGHT) {
	this->WIDTH = WIDTH;
	this->HEIGHT = HEIGHT;
	this->withComputer = new Button();
	this->withComputer->setSize(317, 80);
	this->withComputer->setLocation((WIDTH - 317) / 2, (HEIGHT - 80) / 2 + 175);
	this->withComputer->setTexture((char*)"img/button/gameWithCompuper.png");

	this->forTwo = new Button();
	this->forTwo->setSize(242, 87);
	this->forTwo->setLocation((WIDTH - 242) / 2, (HEIGHT - 87) / 2 + 50);
	this->forTwo->setTexture((char*)"img/button/forTwo.png");

	this->load = new Button();
	this->load->setSize(187, 42);
	this->load->setLocation((WIDTH - 187) / 2, (HEIGHT - 42) / 2 - 60);
	this->load->setTexture((char*)"img/button/load.png");

	this->close = new Button();
	this->close->setSize(128, 50);
	this->close->setLocation((WIDTH - 128) / 2, (HEIGHT - 50) / 2 - 160);
	this->close->setTexture((char*)"img/button/exit.png");
	this->fon = SOIL_load_OGL_texture("img/fon.jpg", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
void Menu::MainMenu::mouse(int button, int state, int ax, int ay,int *stateGame) {
	//std::cout << "x: " << ax << " y: " << ay << std::endl;
	if (button == GLUT_LEFT_BUTTON) {
		if (close->click(ax, HEIGHT - ay)) exit(0);
		if (forTwo->click(ax, HEIGHT - ay)) *stateGame = 3;
		if (withComputer->click(ax, HEIGHT - ay)) *stateGame = 2;
		if (load->click(ax, HEIGHT - ay)) {
			std::ifstream in("save.txt");
			int n;
			in >> n;
			if (n == 1) {
				*stateGame = 7;
			}
			else *stateGame = 6;
			in.close();
		}

	}
}