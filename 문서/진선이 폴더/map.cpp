#include "shader.h"
#include "loadObj.h"

#define SCR_WIDTH 800
#define SCR_HEIGHT 600


GLvoid drawScene(GLvoid);
GLvoid Reshape(int, int);
void Keyboard(unsigned char, int, int);
GLvoid TimerFunction(int);

bool timerCheck = false;
bool culling = true;
bool wire = true;
bool angle_B = true;
bool position = true;

float angle = 0;
int triangle_count = 36;


struct vertex_data {
	float x;
	float y;
	float z;
};

int main(int argc, char** argv)
{
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
	glutKeyboardFunc(Keyboard);
	glutDisplayFunc(drawScene);
	glutTimerFunc(200, TimerFunction, 1);
	glutReshapeFunc(Reshape);
	glutMainLoop();
}


GLvoid drawScene() {

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	glm::mat4 projection = glm::mat4(1.0f);

	projection = glm::ortho(-300 * (float)SCR_WIDTH / (float)SCR_HEIGHT, 300 *(float)SCR_WIDTH / (float)SCR_HEIGHT, (float)-400, (float)400, (float)-400, (float)400);

	glm::vec3 cameraPos = glm::vec3(0.0f, 45.0f, 50);
	glm::vec3 cameraDirection = cameraDirection = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::mat4 view = glm::mat4(1.0f);
	view = glm::lookAt(cameraPos, cameraDirection, cameraUp);

	glm::mat4 rotMatrix = glm::mat4(1.0f); // 단위행렬로초기화 
	glm::mat4 transMatrix = glm::mat4(1.0f);
	glm::mat4 scaleMatrix = glm::mat4(1.0f);
	glm::mat4 myTransformeVector = glm::mat4(1.0f);

	//rotMatrix = glm::rotate(rotMatrix, glm::radians(30.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	//rotMatrix = glm::rotate(rotMatrix, glm::radians(30.0f), glm::vec3(0.0f, 1.0f, 0.0f));

	myTransformeVector = rotMatrix * transMatrix *  scaleMatrix;


	Shader ourShader("vertexshader.glvs", "fragmentshader.glfs"); // you can name your shader files however you like
	ourShader.use();

	loadOBJ road("road.obj", ourShader.ID);
	loadOBJ river("river.obj", ourShader.ID);

	road.load(projection, view);
	road.setTransform(myTransformeVector);
	road.draw();

	transMatrix = glm::translate(transMatrix, glm::vec3(0.0, 0.0, 50.0));
	myTransformeVector = rotMatrix * transMatrix * scaleMatrix;

	river.load(projection, view);
	river.setTransform(myTransformeVector);
	river.draw();

	glutSwapBuffers();
}


GLvoid Reshape(int w, int h) {
	glViewport(0, 0, w, h);
}


void Keyboard(unsigned char key, int x, int y)
{
	switch (key) {
	case 'h':
	case 'H':
		if (culling == true)
			culling = false;
		else
			culling = true;
		break;
	case 'w':
	case 'W':
		if (wire == true)
			wire = false;
		else
			wire = true;
		break;
	case 'y':
	case 'Y':
		timerCheck = true;
		glutTimerFunc(200, TimerFunction, 1);
		break;
	case 'p':
	case 'P':
		break;
	}
	glutPostRedisplay();
}


GLvoid TimerFunction(int value)
{
	if (timerCheck == true) {
		angle += 10;
		glutTimerFunc(200, TimerFunction, 1);
	}

	glutPostRedisplay();
}

