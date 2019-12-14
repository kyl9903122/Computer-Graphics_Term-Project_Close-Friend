#include "MainGame_State.h"
#include "Title_State.h"

Title_State title;
MainGame_State main_game;

GLvoid drawScene();
GLvoid Reshape(int w, int h);
GLvoid TimerFunction(int value);
GLvoid keyboard(unsigned char key, int x, int y);

int state_mode = 0;

int main(int argc, char** argv)
{
	srand((unsigned int)time(NULL));
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(900, 700);
	glutCreateWindow("Floating Window");
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK) {
		std::cerr << "Unable to initialize GLEW" << std::endl;
		exit(EXIT_FAILURE);
	}
	else
		std::cout << "GLEW Initialized" << std::endl;
	title.shader = new Shader("font_vertexshader.glvs", "font_fragmentshader.glfs");
	main_game.shader = new Shader("vertexshader.glvs", "fragmentshader.glfs");
	main_game.hero_shader = new Shader("hero_vertexshader.glvs", "hero_fragmentshader.glfs");

	glutDisplayFunc(drawScene);
	glutTimerFunc(10, TimerFunction, 1);
	glutKeyboardFunc(keyboard);
	glutReshapeFunc(Reshape);
	glutMainLoop();

	delete title.shader;
	delete main_game.shader;
	delete main_game.hero_shader;
}

GLvoid drawScene() 
{
	std::cout << "draw" << std::endl;
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	switch (state_mode) {
	case 0:
		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
		break;
	case 1:
		glClearColor(0.5f, 0.9f, 0.4f, 1.0f);
		break;
	}
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	switch (state_mode) {
	case 0:
		title.Display();
		break;
	case 1:
		main_game.Display();
		break;
	}
	glutSwapBuffers();
}


GLvoid Reshape(int w, int h) {
	glViewport(0, 0, w, h);
}

GLvoid TimerFunction(int value)
{
	switch (state_mode) {
	case 0:
		title.update();
	case 1:
		main_game.update();
		break;
	}

	glutTimerFunc(10, TimerFunction, 1);
	glutPostRedisplay();
}

GLvoid keyboard(unsigned char key, int x, int y) {
	switch (state_mode) {
	case 0:
		title.keyboard(key, x, y);
		break;
	case 1:
		main_game.keyboard(key, x, y);
		break;
	}
	state_mode = title.next_state;
}