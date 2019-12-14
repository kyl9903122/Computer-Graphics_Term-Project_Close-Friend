#include "MyLog.h"

MyLog::MyLog(MyPos road_pos) {
	// pos init
	pos = { road_pos.x - 600.0f, road_pos.y, road_pos.z };
	speed = rand() % 25 + 5;
	size = 50.0f;
	direction = 1;
}

void MyLog::draw(glm::mat4 projection, glm::mat4 view, glm::mat4 model, Shader shader) {
	loadOBJ obj(obj_path, shader.ID);
	shader.use();
	obj.load(projection, view);

	// change road's positoin 
	model = glm::translate(model, glm::vec3(pos.x, 0.0f, 0.0f));
	model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0, 0.0f));

	obj.setTransform(model);

	obj.draw();
}

void MyLog::move(MyPos road_pos) {
	pos.x += speed * direction;
}

bool MyLog::check_removing() {
	if (pos.x > 400 && pos.z <= 600)
		return true;
	return false;
}