#pragma once
#include "loadObj.h"
#include "MyHeader.h"

class kyrHero
{
public:
	// hero's shader_path
	MyPos current_pos{ 0.0f,0.0f,400.0f };
	float direction_angle = 0.0f;
	MyBoundingBox bounding_box{ size / 2,size / 2,size / 2,-size / 2,-size / 2,-size / 2 };
	float size = 40.0f;
	// jumping values
	bool moving = false;
	float jumping_velocity = 30.0f;
	MyPos soul_pos{ 0.0f,0.0f,400.0f };
	bool soul_moving = false;

public:
	void keyboard(unsigned char key, int x, int y);
	bool check_collision(MyPos obs_pos);
	void move();
	bool check_death(MyPos obs_pos, int obs_tag);
	// framework
	void update(/*obs_class*/MyPos test_cube_pos);
	void draw(glm::mat4 projection, glm::mat4 view);
	void soul_move();
	void soul_draw(glm::mat4 projection, glm::mat4 view);
};

