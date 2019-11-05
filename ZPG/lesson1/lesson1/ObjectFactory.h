#pragma once

#include <string>
#include <iostream>
#include "Model.h"
#include "Object.h"
#include <map>
#include "ModelEnum.h"

using namespace std;

/*
enum enum_Model {
	TRIANGLE,
	NONE
};
*/

class ObjectFactory
{
private:
	void createModels();
public:
	Object* createObject(Model_Enum model_type);
	Object* createObject(Model_Enum model_type, glm::vec4 color);
	Model* triangle;
	map<Model_Enum, Model*>* mp;


	ObjectFactory();
	~ObjectFactory();
};

