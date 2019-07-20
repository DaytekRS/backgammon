#include "Game.h"
using namespace Game;
void FieldComputer::check() {
	//если ходит компьютер ищется ход и если он находится, то компьютер его совершает
	//схожа с функцией определения есть ли еще ходы
		if (move == BLACK) {
			exitWhite = true;
			exitBlack = true;
			for (int i = 0; i < 24; i++)
			{
				if (!(i > 5 && i < 12) && points[i].type == BLACK) exitBlack = false;

				if (points[i].count == 0) points[i].type = EMPTY;

				if ((i == 0) && (move == WHITE) && !(head)) continue;
				if ((i == 12) && (move == BLACK) && !(head)) continue;


				if ((stateOne) && (points[i].count != 0) && points[i].type == move)
				{
					int newState = (cube->getStateOne() + i) % 24;
					if (points[newState].type == move || points[newState].type == EMPTY)
					{
						if (move == BLACK && !(i >= 6 && i < 12 && newState > 12 && newState < 24))
						{
							moveChecker(&i, newState, &stateOne);
							cout << "vot "<<i << endl;
							break;
						}
					}
				}
				if ((stateTwo) && (points[i].count != 0) && points[i].type == move)
				{
					int newState = (cube->getStateTwo() + i) % 24;
					if (points[newState].type == move || points[newState].type == EMPTY)
						if (move == BLACK && !(i >= 6 && i < 12 && newState > 12 && newState < 24))

						{
							moveChecker(&i, newState, &stateTwo);
							break;
						}
				}

			}
		}
		//вывод шашки за поле
		if (exitBlack) {
			for (int i = 0; i < 24; i++) {
				if (stateOne || stateTwo) {
					if (move == BLACK) {

						if ((findNearestChecker(1, BLACK) == i && stateOne) || (findNearestChecker(2, BLACK) == i && stateTwo))
						{
							if (findNearestChecker(1, BLACK) == i) stateOne = false;
							if (findNearestChecker(2, BLACK) == i) stateTwo = false;
							points[i].count--;
							countBlack--;
							cout << "vot vihod " << i << endl;
							break;
						}

					}
				}
			}
		}

		//определение есть ли еще ходы
		Field::check();
	}
