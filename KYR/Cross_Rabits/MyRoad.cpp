#include "MyRoad.h"

MyRoad::MyRoad() {
	std::cout << "creating Road..." << std::endl;
	// init pos
	// only its z_pos will change in MyRoad()
	pos = { 0.0f,0.0f,0.0f };

	// init trucks
	/*for (int i = 0; i < 6; ++i) {
		CreateTruck(i);
	}*/
	// let's once make only 1 truck
	CreateTruck(0);

	// init remaining variables
	moving = false;
	// please change
	// you have to change this value when you start map scrolling
	moving_degree = 0;
	std::cout << "complete creating road!" << std::endl;
}

 void MyRoad::draw(glm::mat4 projection, glm::mat4 view)  {
	 Shader shader(vertexshader_path, fragment_path);
	 loadOBJ obj(obj_path, shader.ID);
	 shader.use();
	 obj.load(projection, view);

	 glm::mat4 model = glm::mat4(1.0f);
	 
	 // change road's positoin 
	 model = glm::translate(model,glm::vec3(pos.x, pos.y, pos.z));
	 obj.setTransform(model);

	 obj.draw();
	 trucks[0]->draw(projection, view, model, shader);
}

 void MyRoad::move() {
	 // make trucks move
	/* for (int i = 0; i < 6; ++i) {
		 trucks[i]->move(pos);
		 if (trucks[i]->check_removing())
			 remove_truck(i);
	 }*/
	 trucks[0]->move(pos);
	 if (trucks[0]->check_removing())
		 remove_truck(0);
	 // make road move
	 if (moving) {

	 }
 }

 bool MyRoad::check_removing() {
	 // check its position_y.
	 // if it out off the screen, request removing to state_class
	 return false;
 }

 void MyRoad::CreateTruck(int idx) {
	 trucks[idx] = new MyTruck(pos);
 }

 void MyRoad::remove_truck(int i) {
	 // 1. delete
	 delete trucks[i];

	 // 2. create
	 trucks[i] = new MyTruck(pos);
 }