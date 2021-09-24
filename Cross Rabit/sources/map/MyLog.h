#pragma once
#include "../library/loadObj.h"
#include "../library/MyHeader.h"

class MyLog
{
public:
	MyPos pos;
	const char* obj_path = "../Cross Rabit/resources/models/log.obj";
	float speed;
	float size;
	float direction;
public:
	MyLog(MyPos road_pos, float speed);
	void draw(glm::mat4 projection, glm::mat4 view, glm::mat4 model, Shader shader);
	void move(MyPos road_pos);
	bool check_removing();
	~MyLog();
};
