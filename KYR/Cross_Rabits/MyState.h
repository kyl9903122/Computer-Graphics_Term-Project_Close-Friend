#pragma once
#include "MyHeader.h"
#include "loadOBJ.h"

class MyState
{
protected:
	// current state's position
	MyPos pos;
	// if character move, map move, this varibles check that map is moving
	bool moving;
	// map move each frame, per this degree
	float moving_degree;
	const char* vertexshader_path = "vertexshader.glvs";
	const char* fragment_path = "fragmentshader.glfs";
public:
	MyState() {}
	virtual void draw(glm::mat4 projection, glm::mat4 view) = 0;
	virtual void move() = 0;
	virtual	bool check_removing() = 0;
};

