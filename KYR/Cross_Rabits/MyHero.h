#pragma once
#include "loadObj.h"
#include "MyHeader.h"
#include <vector>

struct MyCollisionData {
	MyPos pos;
	bool use = false;
};

class kyrHero
{
public:
	// hero's shader_path
	MyPos current_pos{ 0.0f,0.0f,00.0f };
	float direction_angle = 0.0f;
	MyBoundingBox bounding_box{ size / 2,size / 2,size / 2,-size / 2,-size / 2,-size / 2 };
	float size = 40.0f;
	// jumping values
	bool moving = false;
	float jumping_velocity = 30.0f;
	MyPos soul_pos{ 0.0f,0.0f,400.0f };
	bool soul_moving = false;
	bool arrive_at_floor = false;
	bool on_the_log = false;
	int log_idx;
	float log_speed = 0;

public:
	void keyboard(unsigned char key, int x, int y);
	bool check_collision(MyPos obs_pos,int obs_tag);
	void move();
	bool check_death(MyPos obs_pos, int obs_tag);
	// framework
	void update(int tag, MyPos* obs_pos, MyPos* obs_pos2,int obs_cnt1, int obs_cnt2);
	void draw(glm::mat4 projection, glm::mat4 view, Shader shader);
	void soul_move();
	void soul_draw(glm::mat4 projection, glm::mat4 view,Shader shader);
	void move_on_the_log(float log_speed);

};

