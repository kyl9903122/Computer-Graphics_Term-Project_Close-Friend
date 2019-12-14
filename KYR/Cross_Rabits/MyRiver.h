#pragma once
#include "MyState.h"
#include "MyLog.h"
class MyRiver : public MyState
{
public:
	MyLog* logs[3];
	const char* obj_path = "river.obj";
public:
	MyRiver();

	void draw(glm::mat4 projection, glm::mat4 view, Shader shader);
	void move();
	bool check_removing();
	void CreateLog(int idx);
	void remove_log(int i);
	MyPos get_obs_pos(int idx);
	float get_obs_speed(int idx);
};

