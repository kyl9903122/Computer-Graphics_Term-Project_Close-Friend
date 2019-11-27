#include "shader.h"
#include "loadObj.h"

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

bool timerCheck = false;

float angle = 0;
float Xpos = -400;

struct vertex_data {
	float x;
	float y;
	float z;
};


class jjsTruck {
public:
	loadOBJ* truck;

	jjsTruck(unsigned int ID) {
		truck = new loadOBJ("truck.obj", ID);
	}

	void move(glm::mat4 myTransformeVector)
	{
		truck->load(projection, view);
		truck->setTransform(myTransformeVector);
		truck->draw();
	}
};


class Road {
public:
	jjsTruck* truck_tmp;
	loadOBJ* road;

	Road(unsigned int ID) {
		truck_tmp = new jjsTruck(ID);
		road = new loadOBJ("road.obj",ID);
	}

	void draw(glm::mat4 transTruck, glm::mat4 transRoad) {
		truck_tmp->move(transTruck);
		road->load(projection, view);
		road->setTransform(transRoad);
		road->draw();
	}
};


int main(int argc, char** argv)
{
	srand((unsigned int)time(NULL));

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

	//좌표축

	glutDisplayFunc(drawScene);
	glutTimerFunc(10, TimerFunction, 1);
	glutReshapeFunc(Reshape);
	glutMainLoop();
}


GLvoid drawScene() 
{
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);


	glm::mat4 rotMatrix = glm::mat4(1.0f); // 단위행렬로초기화 
	glm::mat4 transMatrix = glm::mat4(1.0f);
	glm::mat4 scaleMatrix = glm::mat4(1.0f);


	glm::mat4 myTranstruck = glm::mat4(1.0f);
	glm::mat4 myTransroad = glm::mat4(1.0f);
	glm::mat4 mytransTruckMatrix = glm::mat4(1.0f);
	glm::mat4 myrotTruckMatrix = glm::mat4(1.0f);

	
	myTranstruck = rotMatrix * transMatrix *  scaleMatrix;
	myTransroad = transMatrix;

	Shader ourShader("vertexshader.glvs", "fragmentshader.glfs"); // you can name your shader files however you like
	ourShader.use();

	mytransTruckMatrix = glm::translate(mytransTruckMatrix, glm::vec3(0.0, 0.0, Xpos));
	myrotTruckMatrix = glm::rotate(myrotTruckMatrix, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));

	myTranstruck = myrotTruckMatrix * mytransTruckMatrix *  scaleMatrix;
	myTransroad = transMatrix;

	Road tmp1(ourShader.ID);
	tmp1.draw(myTranstruck, myTransroad);

	glutSwapBuffers();
}


GLvoid Reshape(int w, int h) {
	glViewport(0, 0, w, h);
}

GLvoid TimerFunction(int value)
{
	Xpos += 10;
	glutTimerFunc(10, TimerFunction, 1);
	glutPostRedisplay();
}