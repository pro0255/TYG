#include "Camera.h"



const float MOUSE_SENSITIVITY = 0.1f;

Camera::~Camera()
{
}

Camera::Camera()
{
	this->leftMovement = false;
	this->rightMovement = false;
	this->forwardMovemenet = false;
	this->backMovement = false;
	this->shader = nullptr;
	this->cameraSpeed = 0.4;
	this->eye = glm::vec3(0.0f, 0.0f, 5.0f);
	this->target = glm::vec3(0.0f, 0.0f, -1.0f);
	this->up = glm::vec3(0.0f, 1.0f, 0.0f);
	this->zoom = 45.0f;
	//this->right = glm::vec3(0.0f, 0.0f, 0.0f);
	this->projectionMatrix = glm::perspective(glm::radians(this->zoom), 4.0f / 3.0f, 0.1f, 100.0f);
	this->pitch = 0.0f;
	this->yaw = -90.0f;
	this->updateVectors();
}



glm::vec3 Camera::getEye()
{
	return this->eye;
}

glm::mat4 Camera::getCamera()
{
	//this->updateVectors();
	this->viewMatrix = glm::lookAt(this->eye, this->eye + this->target, this->up);
	return this->viewMatrix;
}

glm::mat4 Camera::getProjectionMatrix()
{
	return this->projectionMatrix;
}

void Camera::updateVectors()
{
	this->target.x = cos(glm::radians(this->yaw));
	this->target.z = sin(glm::radians(this->yaw));
	this->target.y = sin(glm::radians(this->pitch));
	this->target = glm::normalize(this->target);

	this->right = glm::normalize(glm::cross(this->target, glm::vec3(0.0f, 1.0f, 0.0f)));
	this->up = glm::normalize(glm::cross(this->right, this->target));
}

void Camera::notify()
{

	if (this->shader != nullptr) {
		this->updateVectors();
		this->shader->updateCamera();
	}
	else {
		cout << "I have on camera NULLPTR !!!";
	}
}

void Camera::setShader(Shader* shader)
{
	this->shader = shader;
	cout << "Setting shader and after i will notify him with my start parameters" << endl;
	this->notify();
}

void Camera::toFront()
{
	this->eye += this->target * this->cameraSpeed;
}

void Camera::toRight()
{
	this->eye += this->right * this->cameraSpeed;
}

void Camera::toLeft()
{
	this->eye -= this->right * this->cameraSpeed;
}

void Camera::toBack()
{
	this->eye -= this->target * this->cameraSpeed;
}


void Camera::processKeyMovement()
{
	if (this->forwardMovemenet) this->toFront();
	if (this->backMovement) this->toBack();
	if (this->rightMovement) this->toRight();
	if (this->leftMovement) this->toLeft();
	notify();
}

void Camera::pressMove(Movement type)
{
	switch (type) {
	case FORWARD:
		this->forwardMovemenet = !this->forwardMovemenet;
		break;
	case BACK:
		this->backMovement = !this->backMovement;
		break;
	case RIGHT:
		this->rightMovement = !this->rightMovement;
		break;
	case LEFT:
		this->leftMovement = !this->leftMovement;
		break;
	}
}

void Camera::mouseMove(float xOffSet, float yOffSet)
{
	xOffSet *= MOUSE_SENSITIVITY;
	yOffSet *= MOUSE_SENSITIVITY;

	this->yaw += xOffSet;
	this->pitch += yOffSet;

	if (this->pitch > 89.0f) {
		this->pitch = 89.0f;
	}
	if (this->pitch < -89.0f) {
		this->pitch = -89.0f;
	}
	//notify();
}

void Camera::scrollMove(float yOffSet)
{
	cout << "Scroll move" << endl;
	if (zoom >= 1.0f && zoom <= 45.0f) {
		zoom -= yOffSet;
	}
	if (zoom <= 1.0f) {
		zoom = 1.0f;
	}
	if (zoom >= 45.0f) {
		zoom = 45.0f;
	}
	this->projectionMatrix = glm::perspective(glm::radians(this->zoom), 4.0f / 3.0f, 0.1f, 100.0f);
	//notify();
}

