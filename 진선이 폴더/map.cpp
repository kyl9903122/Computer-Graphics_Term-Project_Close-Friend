#include "shader.h"
#include "loadObj.h"
#include "MyRoad.h"
#include "MyTruck.h"
#include "MyRiver.h"
#include "MyLog.h"
#include "MyTrail.h"
#include "MyTrain.h"
#include "MyCommon.h"
#include "MyTree.h"

#define SCR_WIDTH 800
#define SCR_HEIGHT 600

glm::mat4 projection = glm::ortho(-300 * (float)SCR_WIDTH / (float)SCR_HEIGHT, 300 * (float)SCR_WIDTH / (float)SCR_HEIGHT, (float)-400, (float)400, (float)-600, (float)600);

glm::vec3 cameraPos = glm::vec3(8.0f, 45.0f, 40);
glm::vec3 cameraDirection = cameraDirection = glm::vec3(0.0f, 0.0f, 0.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
glm::mat4 view = glm::lookAt(cameraPos, cameraDirection, cameraUp);

GLvoid drawScene(GLvoid);
GLvoid Reshape(int, int);
GLvoid TimerFunction(int);

int map_count = 23;
MyState** states = new MyState*[map_count];

bool timerCheck = false;

void init_map();

Shader *shader;

int main(int argc, char** argv)
{
	srand((unsigned int)time(NULL));
	init_map();
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(900, 700);
	glutCreateWindow("Floating Window");
	glClearColor(0.5f, 0.9f, 0.4f, 1.0f);
	glewExperimental = GL_TRUE;

	if (glewInit() != GLEW_OK) {
		std::cerr << "Unable to initialize GLEW" << std::endl;
		exit(EXIT_FAILURE);
	}
	else
		std::cout << "GLEW Initialized" << std::endl;

	std::cout << "½¦ÀÌ´õ" << std::endl;
	shader = new Shader("vertexshader.glvs", "fragmentshader.glfs");

	glutDisplayFunc(drawScene);
	glutTimerFunc(10, TimerFunction, 1);
	glutReshapeFunc(Reshape);
	glutMainLoop();

	delete shader;
}

GLvoid drawScene() 
{
	std::cout << "draw" << std::endl;
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	for (int i = 0; i < map_count; i++) {
		states[i]->draw(projection, view, *shader);
		if (states[i]->check_removing()) {
			std::cout << "»èÁ¦ : " << i << std::endl;
			delete states[i];
			int create_state_random = rand() % 5;
			switch (create_state_random)
			{
			case 0:
				states[i] = new MyRoad;
				break;
			case 1:
				states[i] = new MyRiver;
				break;
			case 2:
				states[i] = new MyTrail;
				break;
			default:
				states[i] = new MyCommon;
				break;
			}
			states[i]->pos.z = -545;
		}
	}
	glutSwapBuffers();
}


GLvoid Reshape(int w, int h) {
	glViewport(0, 0, w, h);
}

GLvoid TimerFunction(int value)
{
	// change this code into using 'for'
	for (int i = 0; i < map_count; i++) {
		states[i]->move();
		states[i]->pos.z += 5;
	}

	glutTimerFunc(10, TimerFunction, 1);
	glutPostRedisplay();
}

void init_map() {
	//create states
	for (int i = 0; i < map_count; i++) {
		int create_state_random = rand() % 5;
		switch (create_state_random)
		{
		case 0:
			states[i] = new MyRoad;
			break;
		case 1:
			states[i] = new MyRiver;
			break;
		case 2:
			states[i] = new MyTrail;
			break;
		default:
			states[i] = new MyCommon;
			break;
		}
		states[i]->pos.z = i * -50;
	}
}