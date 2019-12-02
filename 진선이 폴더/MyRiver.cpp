#include "MyRiver.h"

MyRiver::MyRiver() {
	std::cout << "creating River..." << std::endl;
	// init pos
	// only its z_pos will change in MyRiver()
	pos = { 0.0f,0.0f,0.0f };

	// init logs
	for (int i = 0; i < 3; ++i) {
		CreateTruck(i);
	}
	// let's once make only 1 truck

	// init remaining variables
	moving = false;
	// please change
	// you have to change this value when you start map scrolling
	moving_degree = 0;
	std::cout << "complete creating River!" << std::endl;
}

void MyRiver::draw(glm::mat4 projection, glm::mat4 view) {
	Shader shader(vertexshader_path, fragment_path);
	loadOBJ obj(obj_path, shader.ID);
	shader.use();
	obj.load(projection, view);

	glm::mat4 model = glm::mat4(1.0f);

	// change road's positoin 
	model = glm::translate(model, glm::vec3(pos.x, pos.y, pos.z));

	//Ä«¸Þ¶ó º¤ÅÍ 
	shader.setVec3("viewPos", glm::vec3(0.0f, 45.0f, 50));
	shader.setVec3("lightColor", glm::vec3(1.0f, 1.0f, 0.9f));
	shader.setVec3("lightPos", glm::vec3(0, 800, 2000));
	obj.setTransform(model);

	obj.draw();
	for (int i = 0; i < 3; i++)
		logs[i]->draw(projection, view, model, shader);
}

void MyRiver::move() {
	// make logs move
	for (int i = 0; i < 3; ++i) {
		logs[i]->move(pos);
		if (logs[i]->check_removing())
			remove_truck(i);
	}

	// make road move
	if (moving) {

	}
}

bool MyRiver::check_removing() {

	// check its position_y.
	// if it out off the screen, request removing to state_class
	if (pos.z > 400)
		return true;
	return false;
}

void MyRiver::CreateTruck(int idx) {
	logs[idx] = new MyLog(pos);
}

void MyRiver::remove_truck(int i) {
	// 1. delete
	delete logs[i];

	// 2. create
	logs[i] = new MyLog(pos);
}