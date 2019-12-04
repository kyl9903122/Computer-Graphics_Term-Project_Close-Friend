#pragma once
#include "MyState.h"
#include "MyTrain.h"
class MyTrail : public MyState
{
private:
	MyTrain* trains[1];
	const char* obj_path = "trail.obj";

public:
	MyTrail();
	void draw(glm::mat4 projection, glm::mat4 view, Shader shader);
	void move();
	bool check_removing();
	void CreateTrain(int idx);
	void remove_train(int i);
	~MyTrail();
};
