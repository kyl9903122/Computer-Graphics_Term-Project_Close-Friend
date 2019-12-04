#include "MyTruck.h"

MyTruck::MyTruck(MyPos road_pos) {
	// pos init
	pos = { road_pos.x-600.0f,road_pos.y,road_pos.z };
	speed = rand() % 20 + 5;
	size = 50.0f; 
	direction = 1;
	if (speed < 10)
		obj_path = "truck.obj";
	else
		obj_path = "car.obj";
}

void MyTruck::draw(glm::mat4 projection, glm::mat4 view, glm::mat4 model, Shader shader) {
	loadOBJ obj(obj_path, shader.ID);
	shader.use();
	obj.load(projection, view);

	// change road's positoin 
	model = glm::translate(model, glm::vec3(pos.x, 0.0f, 0.0f));
	model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0, 0.0f));
	obj.setTransform(model);

	//Ä«¸Þ¶ó º¤ÅÍ 
	shader.setVec3("viewPos", glm::vec3(0.0f, 45.0f, 50));
	shader.setVec3("lightColor", glm::vec3(1.0f, 1.0f, 0.9f));
	shader.setVec3("lightPos", glm::vec3(0, 800, 2000));

	obj.draw();
}

void MyTruck::move(MyPos road_pos) {
	pos.x += speed*direction;
}

bool MyTruck::check_removing() {
	// request removing to road class
	if (pos.x > 450 && pos.z <= 600)
		return true;

	return false;
}

MyTruck::~MyTruck() {};