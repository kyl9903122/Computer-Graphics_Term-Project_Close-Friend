#include "shader.h"
#include "loadObj.h"
#include "MyRoad.h"
#include "MyTruck.h"

#define SCR_WIDTH 800
#define SCR_HEIGHT 600

glm::mat4 projection = glm::ortho(-300 * (float)SCR_WIDTH / (float)SCR_HEIGHT, 300 * (float)SCR_WIDTH / (float)SCR_HEIGHT, (float)-400, (float)400, (float)-400, (float)400);

glm::vec3 cameraPos = glm::vec3(0.0f, 45.0f, 50);
glm::vec3 cameraDirection = cameraDirection = glm::vec3(0.0f, 0.0f, 0.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
glm::mat4 view = glm::lookAt(cameraPos, cameraDirection, cameraUp);


GLvoid drawScene(GLvoid);
GLvoid Reshape(int, int);
GLvoid TimerFunction(int);

// let's make only 1
MyState** states = new MyState*[12];

bool timerCheck = false;

float angle = 0;
float Xpos = -400;

void init_map();

int main(int argc, char** argv)
{
	srand((unsigned int)time(NULL));
	init_map();
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(900, 700);
	glutCreateWindow("Floating Window");
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK) {
		std::cerr << "Unable to initialize GLEW" << std::endl;
		exit(EXIT_FAILURE);
	}
	else
		std::cout << "GLEW Initialized" << std::endl;

	//ÁÂÇ¥Ãà

	glutDisplayFunc(drawScene);
	glutTimerFunc(10, TimerFunction, 1);
	glutReshapeFunc(Reshape);
	glutMainLoop();
}


GLvoid drawScene() 
{
	std::cout << "draw" << std::endl;
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	states[0]->draw(projection,view);

	glutSwapBuffers();
}


GLvoid Reshape(int w, int h) {
	glViewport(0, 0, w, h);
}

GLvoid TimerFunction(int value)
{
	// change this code into using 'for'
	states[0]->move();
	if (states[0]->check_removing) {
		delete states[0];
		states[0] = new MyRoad;
	}
	glutTimerFunc(10, TimerFunction, 1);
	glutPostRedisplay();
}

void init_map() {
	//create states
	//lets make only 1
	states[0] = new MyRoad;
}