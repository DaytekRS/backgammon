#include"Game.h"

using namespace Game;
GameForTwo::GameForTwo(int *state) {
	bSave.setTexture((char*)"img/button/save.png");
	bSave.setSize(210,42);
	bSave.setLocation(655,100);
	field = new Field();
	this->state = state;
}
GameForTwo::~GameForTwo() {
	delete field;
}
void GameForTwo::draw() {
	field->draw();
	bSave.draw();
	if (field->getCountWhite() == 0 || field->getCountBlack() == 0) {
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(0, WIDTH, 0, HEIGHT, -1, 1);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glutReshapeWindow(540, 540);
		centerOnScreen(540, 540);

		if (field->getCountBlack() == 0) *state = 5;
		else *state = 4;
	}
}

void GameForTwo::mouse(int button, int state, int ax, int ay, int *stateGame) {
	if (button == GLUT_LEFT_BUTTON) {
		field->mouse(button, state, ax, ay, stateGame);
		if (bSave.click(ax, HEIGHT-ay)) {
			cout << "work";
			save();
		}
	}
}
void GameForTwo::save() {
	ofstream out("save.txt");
	out << 2 << endl;
	for (int i = 0; i < 30; i++) 
	{
		out << (field->getPoint()[i]).type << " " << (field->getPoint()[i]).count << " " << endl;
	}
	out << field->getCube()->getStateOne() << " " << field->getCube()->getStateTwo() << endl;
	out << field->getStateOne() << " " << field->getStateTwo() << endl;
	out << field->getMove();
	out << field->getCube()->getHaveDouble();
	out.close();
	MessageBox(0, "Игра сохранена", "Нарды", MB_OK);
}
void GameForTwo::load() {
	ifstream in("save.txt");
	int n;
	in >> n;
	Point points[30];
	for (int i=0; i < 30; i++)
	{
		cout << i << endl;
		in >> points[i].type >> points[i].count;
	}

	field->setPoint(points);
	int stateOne, stateTwo;
	in >> stateOne>>stateTwo;
	field->getCube()->setState(stateOne, stateTwo);
	bool bStateOne, bStateTwo;
	in >> bStateOne >> bStateTwo;
	field->setState(bStateOne, bStateTwo);
	int move;
	in >> move;
	field->setMove(move);
	in >> bStateOne;
	field->getCube()->setHaveDouble(bStateOne);
	in.close();

}