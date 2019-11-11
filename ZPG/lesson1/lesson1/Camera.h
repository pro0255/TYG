#pragma once
#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include <glm/gtc/type_ptr.hpp> // glm::value_ptr
#include "Shader.h"
#include "MovementEnum.h"
//priste za tridy applikace, renderer, shader, object, model, camera, window, 
//renderer dostane scenu a tu vyrendruje
class Shader;
//pohledova a view matice
class Camera
{

private:
	//Shader *m_shader;

	glm::vec3 eye;
	glm::vec3 target;
	glm::vec3 up;
	glm::vec3 right;



	bool rightMovement;
	bool forwardMovemenet;
	bool backMovement;
	bool leftMovement;


	float pitch;
	float yaw;
	float zoom;

	float cameraSpeed;

	Shader* shader;

	void toFront();
	void toRight();
	void toLeft();
	void toBack();
	void updateVectors();

public:
	Camera();
	~Camera();

	void notify();
	void setShader(Shader* shader);


	void processKeyMovement();

	void pressMove(Movement type);
	void mouseMove(float xOffSet, float yOffSet);
	void scrollMove(float yOffSet);

	glm::mat4 projectionMatrix;
	glm::mat4 viewMatrix;


	glm::vec3 getEye();
	glm::mat4 getCamera();
	glm::mat4 getProjectionMatrix();
};

