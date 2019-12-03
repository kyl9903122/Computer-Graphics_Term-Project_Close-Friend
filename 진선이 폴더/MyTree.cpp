#include "MyTree.h"

MyTree::MyTree(MyPos road_pos) {
	// pos init
	pos = { (float)((rand() % 24 - 12) * 50),road_pos.y,road_pos.z };
	size = 50.0f;
}

void MyTree::draw(glm::mat4 projection, glm::mat4 view, glm::mat4 model, Shader shader) {
	loadOBJ obj(obj_path, shader.ID);
	shader.use();
	obj.load(projection, view);

	// change road's positoin 
	model = glm::translate(model, glm::vec3(pos.x, 0.0f, 0.0f));
	model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0, 0.0f));
	obj.setTransform(model);

	obj.draw();
}

void MyTree::move(MyPos road_pos) {
}

bool MyTree::check_removing() {
	return false;
}