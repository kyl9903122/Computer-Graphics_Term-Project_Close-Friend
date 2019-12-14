#pragma once
#include "MyState.h"
#include "MyTruck.h"
class MyRoad : public MyState
{
private:
	MyTruck* trucks[2];
	const char* obj_path = "road.obj";
public:
	MyRoad();
	void draw(glm::mat4 projection, glm::mat4 view, Shader shader);
	void move();
	bool check_removing();
	void CreateTruck(int idx);
	void remove_truck(int i);
	~MyRoad();
	MyPos get_obs_pos(int idx);
	float get_obs_speed(int idx) { return 0; };
};

