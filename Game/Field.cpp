#include "Game.h"
using namespace Game;

//инициализация поля
Field::Field() {
	exitWhite = false; //белые не могут выйти за поле
	exitBlack = false; //черные не могут выйти за поле
	head = true; //можем взять с головы
	stateOne = true; //можем взять значание с первого кубика
	stateTwo = true; //можем взять значение со второго кубика
	lastPoint = -1; //номер выбранного пункта, -1 если не выбран
	bBack.setTexture((char*)"img/button/back.png");
	bBack.setLocation(700, 25);
	bBack.setSize(123, 48);
	canMove = true;
	x = 25;
	y = 25;
	//создаем кубик
	cube = new Cube();
	cube->setLocation(685, 425);
	cube->setSize(50, 50);
	cube->setSpace(25);
	//если на первом кубике больше костей ходят белые, если на втором то черные,если равно то кубик перебрасывается
	while (cube->getStateOne() == cube->getStateTwo()) cube->cast();
	if (cube->getStateOne() > cube->getStateTwo()) move = WHITE;
	else move = BLACK;
	//можем ли использовать голову два раза
	usedHeadDouble = !cube->getHaveDouble();
	bCube.setTexture((char*)"img/button/cube.png");
	bCube.setLocation(665, 325);
	bCube.setSize(168,82);

	bMove.setLocation(620, 525);
	

	countBlack = 10;
	countWhite = 10;
	field = SOIL_load_OGL_texture("img/field.jpg", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);
	white = SOIL_load_OGL_texture("img/white.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);
	black = SOIL_load_OGL_texture("img/black.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);

	points[0].count = countBlack;
	points[0].type = WHITE;
	
	points[12].type = BLACK;
	points[12].count = countWhite;


}
Field::~Field() {
	delete cube;
}
void Field::check() {
	//функция проверки есть ли следующий ход
	canMove = false;
	exitWhite = true;
	exitBlack = true;
	for (int i = 0; i < 24; i++) 
	{
		if (i >= 0 && i < 18 && points[i].type == WHITE) exitWhite = false; //если не все фишки одного типа дома, то вывести их нельзя
		if (!(i >5 && i < 12) && points[i].type == BLACK) exitBlack = false;

		if (points[i].count == 0) points[i].type = EMPTY; // если на пункте нет фишек помечаем его пустым

		if ((i == 0) && (move == WHITE) && !(head)) continue; //если нельзя снять с головы не выполняем дальнейшие проверки с ней
		if ((i == 12) && (move == BLACK) && !(head)) continue;
		
		
		if ((stateOne)&&(points[i].count!=0)&&points[i].type==move) //если можно походить первым кубиком и на выбранном пункте
			//есть фишки, игрока который сейчас ходит
		{
			int newState = (cube->getStateOne() + i) % 24 ; //находим новую позицию
			if (points[newState].type == move || points[newState].type == EMPTY) //если мы можем на нее перейти
			{
				if   ((move == WHITE && !(i >= 18 && i < 24 && newState >= 0 && newState < 12))//и мы не пытаемся выйти из дома
					||(move == BLACK && !(i >= 6  && i < 12 && newState > 12 && newState < 24)) 
					)
				{
					//cout << "This not work 1" << endl;
					canMove = true;//помечаем что ход совершить можно
				}
			}
		}
		//по аналогии только для второго кубика
		if ((stateTwo) && (points[i].count != 0) && points[i].type == move)
		{
			int newState = (cube->getStateTwo() + i) % 24 ;
			if (points[newState].type == move || points[newState].type == EMPTY)
				if ((move == WHITE && !(i >= 18 && i < 24 && newState >= 0 && newState < 12)) 
				  ||(move == BLACK && !(i >= 6  && i < 12 && newState > 12 && newState < 24))
					)
				{
					//cout << "This not work 2" << endl;
					canMove = true;
				}
		}
		//если у нас есть ходы
		if (stateOne || stateTwo) {
			//и можно вывести фишку, помечаем что ход есть
			if (move == WHITE && exitWhite) {
				canMove = true;
				//cout << "This not work 3" << endl;
			}
			if (move == BLACK && exitBlack) {
				canMove = true;
				//cout << "This not work 4" << endl;
			}
		}
	}
	//если нельзя брать с головы но есть дубль помечаем, что мы можем взять с головы еще раз
	if (!head && !usedHeadDouble) {
		usedHeadDouble = true;
		head = true;
	}
	//если все кубики использованы
	if (!stateOne && !stateTwo) {
		//проверяем есть ли дубль, если был то даем еще два хода
		if (cube->getHaveDouble()) {
			stateOne = true;
			stateTwo = true;
			cube->setHaveDouble(false);
			return;
		}
		canMove = false; //если нет то ходов больше нет
		return;
	}


}
void Field::draw() {
	check();
	glutReshapeWindow(WIDTH, HEIGHT);
	centerOnScreen(WIDTH, HEIGHT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, WIDTH, 0, HEIGHT, -1, 1);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	cube->draw();
	if (!canMove) bCube.draw();

	if (move == WHITE) 
	{
		bMove.setTexture((char*)"img/button/moveWhite.png");
		bMove.setSize(243, 48);
	}
	else {
		bMove.setTexture((char*)"img/button/moveBlack.png");
		bMove.setSize(260, 48);
	}
	bMove.draw();
	bBack.draw();
	drawTexture(field, x, y, 550+x, 550+y);
	//рисуем шашки на пунктах 1-6
	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < points[i].count; j++) 
		{
			if (points[i].type == BLACK)
				drawTexture(black, 45 + 43 * i, 40 + 26 * j, 70 + 43 * i, 65 + 26 * j);
			else
				drawTexture(white, 45+43*i, 40+26*j, 70 + 43 * i, 65 + 26 * j);
		}
	}
	//рисуем шашки на пунктах 7-12
	for (int i = 6; i < 12; i++) {
		for (int j = 0; j < points[i].count; j++)
		{
			if (points[i].type==BLACK)
				drawTexture(black, 57 + 43 * i, 40 + 26 * j, 82 + 43 * i, 65 + 26 * j);
			else 
				drawTexture(white, 57 + 43 * i, 40 + 26 * j, 82 + 43 * i, 65 + 26 * j);
		}
	}
	//рисуем шашки на пунктах 13-18
	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < points[i+12].count; j++)
		{
			if (points[i+12].type == BLACK)
				drawTexture(black, 530 - 43 * i, 538 - 26 * j, 555 - 43 * i, 563 - 26 * j);
			else
				drawTexture(white, 530 - 43 * i, 538 - 26 * j, 555 - 43 * i, 563 - 26 * j);
		}
	}
	//рисуем шашки на пунктах 19-24
	for (int i = 6; i < 12; i++) {
		for (int j = 0; j < points[i+12].count; j++)
		{
			if (points[i+12].type == BLACK)
				drawTexture(black, 518 - 43 * i, 538 - 26 * j, 543 - 43 * i, 563 - 26 * j);
			else
				drawTexture(white, 518 - 43 * i, 538 - 26 * j, 543 - 43 * i, 563 - 26 * j);
		}
	}
}
Cube* Field::getCube() {
	return cube;
}
bool  Field::moveChecker(int *lastPoint, int newPoint,bool *state) {
	//перемещение шашки на поле
	if (((*lastPoint == 0) || (*lastPoint == 12)) && (!head)) return false;//если пытаем переместить с головы но это нельзя сделать
	if (*lastPoint == 0 && move == WHITE) head = false; //если снимаем с головы то помечаем, что с нее больше нельзя брать
	if (*lastPoint == 12 && move == BLACK) head = false;
	points[*lastPoint].count--;
	points[newPoint].count++;
	*state = false;
	*lastPoint = -1;
	if (points[newPoint].type == EMPTY) points[newPoint].type = move;
	return true;
}
bool  Field::checkPoint(int ax, int ay,int x,int y,int i) {
	if (ax > x  && ax < x + 45)
	if (ay>y&&ay<y+275){
		cout << lastPoint << " " << i << endl;
	
		//если выбранное поле совпадает с полем, что было выбрано для хода, отменяем это
		if (lastPoint == i) {
			lastPoint = -1;
			return true;
		}
		//если не было выбора и тип фишек на выбранном пункте совпадает с человеком, который ходит
		//запомнить пункт
		if (lastPoint == -1 && points[i].type == move) {
			lastPoint = i;
			return true;
		}
		else {

			//если фишка дошла до дома, запрещаем ей вернуться в начало
			if (move == BLACK && lastPoint > 5 && lastPoint < 12 && i>11 && i < 24) {
				lastPoint = -1;
				return false;
			}
			if (move == WHITE && lastPoint > 17 && lastPoint < 24 && i >= 0 && i < 12) {
				lastPoint = -1;
				return false;
			}
			//если выбранный пункт находится на растоянии одной из выпавших костей и тип фишек
			//совпадает с теми, что на выбранной доске совершить ход
			if ((points[i].type == move || points[i].type == EMPTY) && lastPoint != -1) {
				if ((i+23 - lastPoint)%24+1 == cube->getStateOne() && stateOne) {
					if (moveChecker(&lastPoint, i, &stateOne)) return true;
				}
				else if ((i+23 - lastPoint) % 24+1 == cube->getStateTwo() && stateTwo) {
					if (moveChecker(&lastPoint, i, &stateTwo)) return true;
				}
				
			}
			//выбранный пункт не годится для хода, но тип фишек на нем совпадает с теми, кто ходит
			//значит пробуем ходить с него
			if (points[i].type == move && lastPoint != -1) {
				lastPoint = i;
				return true;
			}

		}
	}
	
	return false;
}

int Field::findNearestChecker(int mode,int state) {
	//ищем ближайший пункт к кубику
	int cubeBone;
	if (state == BLACK) {
		if (mode == 1) cubeBone = 13- cube->getStateOne();
		else cubeBone = 13- cube->getStateTwo();
	}
	else
	{
		if (mode == 1) cubeBone = 24 - cube->getStateOne();
		else cubeBone = 24 - cube->getStateTwo();
	}
	cout << "1 cubeBone " << cubeBone<<endl;
	if (points[cubeBone].count != 0) return cubeBone;
	else 
	{
		for (int i = 0;; i++) {
			cout << "2 cubeBone " << cubeBone<<endl;
			if (cubeBone + i < 24) 
			{
				if (points[cubeBone + i].count != 0) return cubeBone+i;
			}

			if (cubeBone - i >= 0)
			{
				if (points[cubeBone - i].count != 0) return cubeBone-i;
			}
		}
	
	}
}

void Field::mouse(int button, int state, int ax, int ay, int *stateGame) {
	//обработка клавиш мыши
	if (button == GLUT_LEFT_BUTTON) {
		//нажатие на бросить кубик
		if (bCube.click(ax, HEIGHT - ay)&&!canMove) {
			if (state == 1) {
				cube->cast();
				stateOne = true;
				stateTwo = true;
				if (move == WHITE) move = BLACK;
				else move = WHITE;

				canMove = true;
				head = true;
				usedHeadDouble = !cube->getHaveDouble();
			
			}
			return;
		}
		//нажать на назад
		if (bBack.click(ax, HEIGHT - ay)) {
			glutReshapeWindow(540, 540);
			centerOnScreen(540, 540);
			*stateGame = 0;
			return;
		}
		
		if (state == 1&&canMove) {
			for (int i = 0; i < 6; i++)
				if (checkPoint(ax, HEIGHT - ay, 34 + i * 43, this->y, i)) return;
			for (int i = 6; i < 12; i++)
				if (checkPoint(ax, HEIGHT-ay, 46 + i * 43, this->y, i)) return;
			for (int i = 0; i < 6; i++)
				if (checkPoint(ax, HEIGHT - ay, 34 + i * 43, this->y+275, 23-i)) return;
			for (int i = 6; i < 12; i++)
				if (checkPoint(ax, HEIGHT - ay, 46 + i * 43, this->y+275, 23-i)) return;

			if (exitWhite&&move == WHITE && lastPoint != -1  && !(ax>=x&&ax<=x+550&&(HEIGHT-ay)>=y&& (HEIGHT - ay)<=550)) {
				cout << "findNearestChecker 1:  " << findNearestChecker(1, WHITE) << "findNearestChecker 2: " << findNearestChecker(2, WHITE) << endl;
				if ((findNearestChecker(1, WHITE) == lastPoint && stateOne) || (stateTwo&&findNearestChecker(2, WHITE) == lastPoint))
				{
					if (findNearestChecker(1, WHITE) == lastPoint) stateOne = false;
					if (findNearestChecker(2, WHITE) == lastPoint) stateTwo = false;
					points[lastPoint].count--;
					countWhite--;
				}
			}

			if (exitBlack&&move == BLACK && lastPoint != -1 && !(ax >= x && ax <= x + 550 && (HEIGHT - ay) >= y && (HEIGHT - ay) <= 550)) {
				cout << "findNearestChecker 1:  " << findNearestChecker(1, BLACK) << "findNearestChecker 2: " << findNearestChecker(2, BLACK) << endl;
				if ((findNearestChecker(1,BLACK) == lastPoint&&stateOne) || (findNearestChecker(2, BLACK) == lastPoint&&stateTwo))
				{
					if (findNearestChecker(1, BLACK) == lastPoint) stateOne = false;
					if (findNearestChecker(2, BLACK) == lastPoint) stateTwo = false;
					points[lastPoint].count--;
					countBlack--;
				}
			}
		}
		
		
	}
}

int Field::getCountWhite() {
	return countWhite;
}


int Field::getCountBlack() {
	return countBlack;
}

void Field::setState(bool one,bool two) {
	stateOne = one;
	stateTwo = two;
}

bool Field::getStateOne() {
	return stateOne;
}
bool Field::getStateTwo() {
	return stateTwo;
}

Point* Field::getPoint() {
	return points;
}

void Field::setPoint(Point* points) {
	for (int i = 0; i < 30; i++) {
		//cout<<"P: " << points[i].count << endl;
		this->points[i] = points[i];
		//cout << this->points[i].count;
	}
}

int Field::getMove() {
	return move;
}
void Field::setMove(int move) {
	this->move = move;
}