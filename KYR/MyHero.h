#pragma once
#include "loadObj.h"
#include "MyHeader.h"
class MyHero
{
private:
	// hero's shader_path
	const char* vertexshader_path = "hero_vertexshader.glvs";
	const char* fragmentshader_path = "hero_fragmentshader.glfs";
	const char* obj_path = "cube2.obj";
	MyPos current_pos{ 0.0f,0.0f,0.0f };
	float direction_angle = 0.0f;
	MyBoundingBox bounding_box{ size / 2,size / 2,size / 2,-size / 2,-size / 2,-size / 2 };
	float size = 40.0f;
	// jumping values
	bool moving = false;
	float jumping_velocity = 30.0f;
public:
	void keyboard(unsigned char key, int x, int y);
	bool check_collision(MyPos obs_pos);
	void move();
	void draw(glm::mat4 projection,glm::mat4 view);
};

