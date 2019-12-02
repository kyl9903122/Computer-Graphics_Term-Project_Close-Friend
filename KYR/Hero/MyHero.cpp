#include "MyHero.h"

void kyrHero::keyboard(unsigned char key, int x, int y) {
	if (!moving) {
		switch (key) {
		case 'w':
		case 'W':
			// move hero to front
			direction_angle = 0.0f;
			break;
		case 'd':
		case 'D':
			//move hero to rihgt
			direction_angle = 90.0f;
			break;
		case 'a':
		case 'A':
			// move hero to left
			direction_angle = -90.0f;
			break;
		default:
			return;
		}
		moving = true;
	}
}

void kyrHero::move() {
	// hero will move to its direction and jump
	// hero move to its direction
	if (moving) {
		switch ((int)direction_angle) {
		case 0:
			// directon == front
			current_pos.z -= 5;
			break;
		case 90:
			// direction == right
			current_pos.x += 5;
			break;
		case -90:
			// direction == left
			current_pos.x -= 5;
			break;
		}
		// hero is jumping
		jumping_velocity -= 6;
		current_pos.y += jumping_velocity;
		if (current_pos.y <= 0.0f) {
			// hero fell to the floor
			// we have to init 'jumping values'
			moving = false;
			jumping_velocity = 30.0f;
			current_pos.y = 0.0f;
		}
	}
}

bool kyrHero::check_collision(MyPos obs_pos) {
	// make obs_bounding_box
	MyBoundingBox obs_bounding_box = {
		obs_pos.x + 25, obs_pos.y + 25, obs_pos.z + 25,
		obs_pos.x - 25,obs_pos.y - 25,obs_pos.z - 25
	};
	// change my_bounding_box
	bounding_box = {
		current_pos.x + size / 2,current_pos.y + size / 2,current_pos.z + size / 2,
		current_pos.x - size / 2,current_pos.y - size / 2,current_pos.z - size / 2
	};
	// start checking
	// aabb - aabb collision checking
	if (bounding_box.right < obs_bounding_box.left)
		return false;

	if (bounding_box.left > obs_bounding_box.right)
		return false;

	if (bounding_box.top < obs_bounding_box.bottom)
		return false;

	if (bounding_box.bottom > obs_bounding_box.top)
		return false;

	if (bounding_box.front < obs_bounding_box.back)
		return false;

	if (bounding_box.back > obs_bounding_box.front)
		return false;

	return true;
}

void kyrHero::draw(glm::mat4 projection, glm::mat4 view) {
	Shader shader(vertexshader_path, fragmentshader_path);
	loadOBJ obj(obj_path, shader.ID);
	shader.use();
	obj.load(projection,view);
	// init model_matrix
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(current_pos.x, current_pos.y, current_pos.z));
	model = glm::rotate(model, glm::radians(direction_angle), glm::vec3(0.0f, 1.0f, 0.0f));

	// apply transform matix
	obj.setTransform(model);

	// draw obj
	obj.draw();
}

bool kyrHero::check_death(MyPos obs_pos,int obs_tag) {
	if (check_collision(obs_pos)) {
		// case 1. collision with obstacles
		if (obs_tag == 1) {
			// obstacle is log

		}
	}
}