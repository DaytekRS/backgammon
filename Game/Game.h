#pragma once
#include<iostream>
#include <vector>
#include "..\Controllers\Controllers.h"
#include "..\gl\glut.h"
#include "..\Soil\SOIL.h"
#include <fstream>
#include"..\Draw\Draw.h"
#include<windows.h>
#define WHITE 1
#define BLACK 2
#define EMPTY 0
#define WIDTH 900
#define HEIGHT  600
using namespace std;
using namespace Controllers;
namespace Game {
	struct Point {
		int type;
		int count;
	};

	class Cube {
		public:
			Cube();
			void setLocation(int, int);
			void setSize(int, int);
			void draw();
			void cast();
			void setSpace(int);
			int getStateOne();
			int getStateTwo();
			bool getHaveDouble();
			void setHaveDouble(bool);
			void setState(int,int);
		private:
			int stateOne, stateTwo; //числа на первом и втором кубике
			int x, y;
			int width, height;
			int space;
			GLuint one, two, three, four, five, six;
			bool haveDouble;
		
	};
	
	class Field {
	public:
		Field();
		~Field();
		void draw();
		Cube* getCube();
		void mouse(int, int, int, int, int*);
		bool moveChecker(int*,int,bool*);
		virtual void check();
		bool checkPoint(int,int,int,int,int);
		int findNearestChecker(int mode,int state);
		int getCountWhite();
		int getCountBlack();
		void setState(bool, bool);
		bool getStateOne();
		bool getStateTwo();
		Point* getPoint();
		void setPoint(Point* points);
		int getMove();
		void setMove(int);
	protected:
		GLuint field, black, white;
		int countBlack, countWhite;
		Point points[30];
		Cube *cube;
		Button bCube,bMove,bBack;
		int x, y;
		int move;
		int lastPoint;
		bool canMove;
		bool stateOne, stateTwo;
		bool head,usedHeadDouble;
		bool exitWhite, exitBlack;
	};

	class FieldComputer: public Field {
		public:
			void check();
	};

	class GameForTwo {
		public:
			GameForTwo(int *);
			~GameForTwo();
			void draw();
			void mouse(int,int,int,int,int*);
			void save();
			void load();
		private:
			Field *field;
			int *state;
			Button bSave;
	};

	class GameComputer {
	public:
		GameComputer(int *);
		~GameComputer();
		void draw();
		void mouse(int, int, int, int, int*);
		void save();
		void load();
	private:
		FieldComputer * field;
		int *state;
		Button bSave;
	};
}
