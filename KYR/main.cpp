#include "loadObj.h"
#include "MyHero.h"

// variables
MyHero hero;

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
	glutCreateWindow("drill_15");
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK) {
		std::cerr << "unable to initialize GLEW" << std::endl;
		exit(EXIT_FAILURE);
	}
	else
		std::cout << "GLEW Initialized\n";
	// main loop
	glutDisplayFunc(Display);
	glutTimerFunc(10, Timer, 1);
	glutKeyboardFunc(keyboard);
	glutMainLoop();
}

void Display() {
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	glm::mat4 projection = glm::mat4(1.0f);
	projection = glm::ortho(-300 * (float)SCR_WIDTH / (float)SCR_HEIGHT, 300 * (float)SCR_WIDTH / (float)SCR_HEIGHT, (float)-400, (float)400, (float)-400, (float)400);

	glm::mat4 view = glm::mat4(1.0f);
	view = glm::lookAt(glm::vec3(0.0f, 45.0f, 50.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));

	hero.draw(projection,view);

	glutSwapBuffers();
}

void Timer(int val) {
	glutPostRedisplay();
	hero.move();
	if (val == 0) {
		return;
	}
	glutTimerFunc(10, Timer, val);
}

void keyboard(unsigned char key, int x, int y) {
	hero.keyboard(key, x, y);
	glutPostRedisplay();
}



