#include "Title_State.h"

void Title_State::Display() {
	draw_font();
}

void Title_State::update() {
	font_sin_angle = (float)(((int)font_sin_angle + 5) % 180);
	obj_pos.z = sin(glm::radians(font_sin_angle));
}

void Title_State::keyboard(unsigned char key, int x, int y) {
	switch (key) {
	default:
		next_state = 1;
		break;
	}
}

void Title_State::draw_font() {
	shader->use();
	loadOBJ font("title_font.obj", shader->ID);
	font.load(projection, view);

	glm::mat4 model = glm::mat4(1.0f);
	glm::mat4 translation = glm::mat4(1.0f);
	glm::mat4 scaling = glm::mat4(1.0f);
	// lightning
	shader->setVec3("viewPos", glm::vec3(0.0f, 45.0f, 50));
	shader->setVec3("lightColor", glm::vec3(0.5f, 0.5f, 0.5f));
	shader->setVec3("lightPos", glm::vec3(0, 800, 2000));

	// transform
	translation = glm::translate(translation, glm::vec3(obj_pos.x, obj_pos.y, obj_pos.z));
	scaling = glm::scale(scaling, glm::vec3(1.0f, 1.0f, 1.0f));
	model = scaling * translation;
	font.setTransform(model);
}