#include "MyHero.h"

void kyrHero::keyboard(unsigned char key, int x, int y) {
	if (!moving && !soul_moving) {
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
	if (moving && !soul_moving) {
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
	Shader shader("hero_vertexshader.glvs", "hero_fragmentshader.glfs");
	loadOBJ obj("cube2.obj", shader.ID);
	shader.use();
	obj.load(projection, view);
	// init model_matrix
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(current_pos.x, current_pos.y, current_pos.z));
	model = glm::rotate(model, glm::radians(direction_angle), glm::vec3(0.0f, 1.0f, 0.0f));

	// apply transform matix
	obj.setTransform(model);

	// draw obj
	obj.draw();
	soul_draw(projection,view);

}

bool kyrHero::check_death(MyPos obs_pos,int obs_tag) {
		// case 1. collision with obstacles
		if (obs_tag == 1) {
			// obstacle is log
			if (check_collision(obs_pos)) {
				// hero is on the log
				current_pos.y = obs_pos.y + 25+size/2;
				// hero has to stop jumping
				moving = false;
				jumping_velocity = 30.0f;
				return false;
			}
			else {
				// hero falls into the river
				std::cout << "fall into the river" << std::endl;
				current_pos.y -= 5;
				moving = false;
				if (current_pos.y < 100) {
					soul_moving = true;
				}
				return true;
			}
		}
		else {
			if (check_collision(obs_pos)) {
				moving = false;
				soul_moving = true;
				return true;
			}
			else
				return false;
		}
}

void kyrHero::update(/*obs_class*/MyPos test_cube_pos) {
	move();
	// this part will change to for()
	if (check_death(test_cube_pos, 0)) {
		//test 
		std::cout << "die!" << std::endl;
	}
	soul_move();
}

void kyrHero::soul_move() {
	if (soul_moving) {
		soul_pos.y += 5;
		soul_pos.x = 20*sin(glm::radians(soul_pos.y));
	}
}

void kyrHero::soul_draw(glm::mat4 projection, glm::mat4 view) {
	if (soul_moving){
		Shader shader("soul_vertexshader.glvs", "soul_fragmentshader.glfs");
		loadOBJ soul_obj("soul_cube.obj", shader.ID);
		soul_obj.load(projection, view);
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.8f, 0.8f, 0.8f));
		model = glm::translate(model, glm::vec3(soul_pos.x+current_pos.x, soul_pos.y+current_pos.y, current_pos.z));

		soul_obj.setTransform(model);
		soul_obj.draw();
	}
}