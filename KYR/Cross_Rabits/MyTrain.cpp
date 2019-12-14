#include "MyTrain.h"



MyTrain::MyTrain(MyPos road_pos) {
	// pos init
	pos = { road_pos.x - 800.0f,road_pos.y,road_pos.z };
	speed = rand()% 20 + 50;
	size = 50.0f;
	direction = 1;

}

void MyTrain::draw(glm::mat4 projection, glm::mat4 view, glm::mat4 model, Shader shader) {
	loadOBJ obj(obj_path, shader.ID);
	shader.use();
	obj.load(projection, view);

	// change road's positoin 
	model = glm::translate(model, glm::vec3(pos.x, 0.0f, 0.0f));
	model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0, 0.0f));
	obj.setTransform(model);

	obj.draw();
}

void MyTrain::move(MyPos road_pos) {
	pos.x += speed * direction*0;
}

bool MyTrain::check_removing() {
	// request removing to road class
	if (pos.x > 1000 && pos.z <= 600)
		return true;
	return false;
}