// this is the main.cpp
#include "MainGameState.h"

MainGameState main_game;


//function
void Display();
void Timer(int);
void keyboard(unsigned char key, int x, int y);

void main(int argc, char** argv) {
	std::cout << "init main" << std::endl;
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(SCR_WIDTH, SCR_HEIGHT);
	glutCreateWindow("Cross Rabit");
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK) {
		std::cerr << "unable to initialize GLEW" << std::endl;
		exit(EXIT_FAILURE);
	}
	else
		std::cout << "GLEW Initialized\n";
	main_game.shader = new Shader("vertexshader.glvs", "fragmentshader.glfs");
	main_game.hero.shader = new Shader("hero_vertexshader.glvs", "hero_fragmentshader.glfs");
	// main loop
	glutTimerFunc(20, Timer, 1);
	glutDisplayFunc(Display);
	glutKeyboardFunc(keyboard);
	glutMainLoop();
}

void Display() {
	//test
	glClearColor(0.5f, 0.9f, 0.4f, 1.0f);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	main_game.Display();
	glutSwapBuffers();
}

void Timer(int val) {
	glutPostRedisplay();
	main_game.Timer(val);
	if (val == 0) {
		return;
	}
	glutTimerFunc(10, Timer, val);
}

void keyboard(unsigned char key, int x, int y) {
	main_game.keyboard(key, x, y);
	glutPostRedisplay();
}




