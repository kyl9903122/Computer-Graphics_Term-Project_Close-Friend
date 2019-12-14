#pragma once
#include "MyState.h"
#include "MyTrain.h"
class MyTrail : public MyState
{
public:
	MyTrain* trains[1];
	const char* obj_path = "trail.obj";

public:
	MyTrail();
	void draw(glm::mat4 projection, glm::mat4 view, Shader shader);
	void move();
	bool check_removing();
	void CreateTrain(int idx);
	void remove_train(int i);
	MyPos get_obs_pos(int idx);
	float get_obs_speed(int idx) { return 0; };
};
