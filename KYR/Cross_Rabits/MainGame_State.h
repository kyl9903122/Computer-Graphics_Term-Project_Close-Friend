#pragma once
#include "MyRoad.h"
#include "MyTruck.h"
#include "MyRiver.h"
#include "MyLog.h"
#include "MyTrail.h"
#include "MyTrain.h"
#include "MyCommon.h"
#include "MyTree.h"
#include "MyHero.h"

class MainGame_State
{
public:
	int change_timer = 50;
	int next_state = 1;
	glm::mat4 projection = glm::ortho(-300 * (float)SCR_WIDTH / (float)SCR_HEIGHT, 300 * (float)SCR_WIDTH / (float)SCR_HEIGHT, (float)-400, (float)400, (float)-600, (float)600);
	glm::vec3 cameraPos = glm::vec3(8.0f, 45.0f, 40);
	glm::vec3 cameraDirection = cameraDirection = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::mat4 view = glm::lookAt(cameraPos, cameraDirection, cameraUp);

	int map_count = 23;
	MyState** states = new MyState * [map_count];
	bool timerCheck = false;
	bool start = false;
	Shader* shader;

	//hero
	Shader* hero_shader;
	kyrHero hero;
	MyPos cur_state_obs_pos[3];
	MyPos next_state_obs_pos[3];
	int cur_state_tag;
	int next_state_tag;
	int cur_state_obs_cnt;
	int next_state_obs_cnt;
	int cur_state_idx = 0;
	int pass_state_cnt = 0;


public:
	MainGame_State();
	~MainGame_State();
	void Display();
	void update();
	void init_map();
	void keyboard(unsigned char key, int x, int y);
	void hero_update();



};

