#pragma once
#include "MyState.h"
#include "MyLog.h"
class MyRiver : public MyState
{
private:
	MyLog* logs[3];
	const char* vertexshader_path = "vertexshader2.glvs";
	const char* fragment_path = "fragmentshader2.glfs";
	const char* obj_path = "river.obj";
public:
	MyRiver();
	void draw(glm::mat4 projection, glm::mat4 view);
	void move();
	bool check_removing();
	void CreateTruck(int idx);
	void remove_truck(int i);
};

