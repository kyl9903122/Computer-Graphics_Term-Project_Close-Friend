#include "MainGame_State.h"

MainGame_State main_game;

GLvoid drawScene();
GLvoid Reshape(int w, int h);
GLvoid TimerFunction(int value);
GLvoid keyboard(unsigned char key, int x, int y);

int main(int argc, char** argv)
{
	srand((unsigned int)time(NULL));
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
	main_game.shader = new Shader("vertexshader.glvs", "fragmentshader.glfs");
	main_game.hero_shader = new Shader("hero_vertexshader.glvs", "hero_fragmentshader.glfs");

	glutDisplayFunc(drawScene);
	glutTimerFunc(10, TimerFunction, 1);
	glutKeyboardFunc(keyboard);
	glutReshapeFunc(Reshape);
	glutMainLoop();

	delete main_game.shader;
	delete main_game.hero_shader;
}

GLvoid drawScene() 
{
	std::cout << "draw" << std::endl;
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	main_game.Display();
	glutSwapBuffers();
}


GLvoid Reshape(int w, int h) {
	glViewport(0, 0, w, h);
}

GLvoid TimerFunction(int value)
{
	main_game.update();

	glutTimerFunc(10, TimerFunction, 1);
	glutPostRedisplay();
}

GLvoid keyboard(unsigned char key, int x, int y) {
	main_game.keyboard(key, x, y);
}