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
#include "MyHero.h"

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
GLvoid keyboard(unsigned char key, int x, int y);

int map_count = 23;
MyState** states = new MyState*[map_count];

bool timerCheck = false;
bool start = false;

void init_map();

Shader *shader;
Shader* hero_shader;

//hero
kyrHero hero;
MyPos cur_state_obs_pos[3];
MyPos next_state_obs_pos[3];
int cur_state_tag;
int next_state_tag;
int cur_state_obs_cnt;
int next_state_obs_cnt;
int cur_state_idx = 0;


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
	hero_shader = new Shader("hero_vertexshader.glvs", "hero_fragmentshader.glfs");
	glutDisplayFunc(drawScene);
	glutTimerFunc(10, TimerFunction, 1);
	glutKeyboardFunc(keyboard);
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

	// hero draw
	hero.draw(projection, view,*hero_shader);
	glutSwapBuffers();
}


GLvoid Reshape(int w, int h) {
	glViewport(0, 0, w, h);
}

GLvoid TimerFunction(int value)
{
	if (start) {
		// change this code into using 'for'
		if (!hero.soul_moving) {
			for (int i = 0; i < map_count; i++) {
				states[i]->move();
				states[i]->pos.z += 5;
			}
		}
		//hero
		cur_state_obs_pos[0] = states[cur_state_idx]->collision_pos[0];
		cur_state_obs_pos[1] = states[cur_state_idx]->collision_pos[1];
		cur_state_obs_pos[2] = states[cur_state_idx]->collision_pos[2];
		cur_state_obs_cnt = states[cur_state_idx]->obs_cnt;
		cur_state_tag = states[cur_state_idx]->tag;
	/*	next_state_obs_pos[0] = states[cur_state_idx + 1]->collision_pos[0];
		next_state_obs_pos[1] = states[cur_state_idx + 1]->collision_pos[1];
		next_state_obs_pos[2] = states[cur_state_idx + 1]->collision_pos[2];
		next_state_obs_cnt = states[cur_state_idx + 1]->obs_cnt;*/
		//next_state_tag = states[cur_state_idx + 1]->tag;
		if (hero.moving && hero.direction_angle == 0.0f) {
			hero.on_the_log = false;
			//hero.update(next_state_tag, cur_state_obs_pos, next_state_obs_pos, 0, next_state_obs_cnt);
			hero.update(cur_state_tag, cur_state_obs_pos, nullptr, cur_state_obs_cnt, 0);
		}
		else if (hero.on_the_log) {
			for (int i = 0; i < 3; ++i) {
				if (hero.check_collision(cur_state_obs_pos[i], cur_state_tag)) {
					hero.log_speed = states[cur_state_idx]->get_obs_speed(i);				
					std::cout << "on_the_log is true" << std::endl;
					break;
				}
			}
			hero.update(cur_state_tag, cur_state_obs_pos, nullptr, cur_state_obs_cnt, 0);
		}
		else {
			hero.update(cur_state_tag, cur_state_obs_pos, nullptr, cur_state_obs_cnt, 0);

		}
		if (hero.arrive_at_floor && hero.direction_angle == 0.0f) {
			std::cout << "arrive at floor" << std::endl;
			hero.arrive_at_floor = false;
			hero.current_pos.z = states[cur_state_idx]->pos.z;
		}
		std::cout << "cur_state_idx: " << cur_state_idx << std::endl;
	}

	glutTimerFunc(10, TimerFunction, 1);
	glutPostRedisplay();
}

void init_map() {
	states[0] = new MyCommon;
	//create states
	for (int i = 1; i < map_count; i++) {
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

GLvoid keyboard(unsigned char key, int x, int y) {
	if (!hero.soul_moving && !hero.moving) {
		switch (key) {
		case 'w':
		case 'W':
			// move hero to front
			hero.direction_angle = 0.0f;
			cur_state_idx = (cur_state_idx + 1) % map_count;
			hero.cur_state_idx = &cur_state_idx;
			break;
		case 'd':
		case 'D':
			//move hero to rihgt
			hero.direction_angle = 90.0f;
			break;
		case 'a':
		case 'A':
			// move hero to left
			hero.direction_angle = -90.0f;
			break;
		default:
			return;
		}
		hero.moving = true;
		start = true;
	}
}