#include "MyTrail.h"
#include<iostream>

MyTrail::MyTrail() {
	std::cout << "creating Trail..." << std::endl;
	// init pos
	// only its z_pos will change in MyTrail()
	pos = { 0.0f,0.0f,0.0f };

	// init trains
	CreateTrain(0);
	
	// let's once make only 1 truck
	//CreateTruck(0);

	// init remaining variables
	moving = false;
	// please change
	// you have to change this value when you start map scrolling
	moving_degree = 0;
	std::cout << "complete creating trail!" << std::endl;
}

void MyTrail::draw(glm::mat4 projection, glm::mat4 view, Shader shader) {
	loadOBJ obj(obj_path, shader.ID);
	shader.use();
	obj.load(projection, view);

	glm::mat4 model = glm::mat4(1.0f);

	// change road's positoin 
	model = glm::translate(model, glm::vec3(pos.x, pos.y, pos.z));
	obj.setTransform(model);

	obj.draw();
	trains[0]->draw(projection, view, model, shader);
}

void MyTrail::move() {
	// make trains move
	trains[0]->move(pos);
	if (trains[0]->check_removing())
		remove_train(0);
	
	if (moving) {

	}
}

bool MyTrail::check_removing() {
	// check its position_y.
	if (pos.z > 600) {
		remove_train(0);
		return true;
	}
	// if it out off the screen, request removing to state_class
	return false;
}

void MyTrail::CreateTrain(int idx) {
	trains[idx] = new MyTrain(pos);
}

void MyTrail::remove_train(int i) {
	// 1. delete
	delete trains[i];

	// 2. create
	if (pos.z <= 600)
		trains[i] = new MyTrain(pos);
}