#pragma once
#include<iostream>
#include "..\Controllers\Controllers.h"
#include "..\gl\glut.h"
#include "..\Soil\SOIL.h"
#include <fstream>
using namespace Controllers;
namespace Menu {
	class MainMenu {
		public:
			MainMenu(GLuint load,int WIDTH, int HEIGHT);
			void draw();
			void mouse(int button, int state, int ax, int ay, int *stateGame);
		private:
			Button * withComputer, *forTwo, *close, *load;
			GLuint fon;
			int WIDTH, HEIGHT;
	};
}
