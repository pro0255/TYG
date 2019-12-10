#include "Camera.h"


//const float MOUSE_SENSITIVITY = 0.1f;
const float Camera::MOUSE_SENSITIVITY = 0.1f;
const float Camera::CAMERA_SPEED = 0.05f;

Camera::~Camera() {}

Camera::Camera()
{
	this->leftMovement = false;
	this->rightMovement = false;
	this->forwardMovemenet = false;
	this->backMovement = false;
	//this->cameraSpeed = 0.5;
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



glm::vec3 Camera::getTarget()
{
	return this->target;
}

glm::vec3 Camera::getEye()
{
	return this->eye;
}

auto Camera::getCamera() -> glm::mat4
{
	this->viewMatrix = glm::lookAt(this->eye, this->eye + this->target, this->up);
	return this->viewMatrix;
}

auto Camera::getProjectionMatrix() const -> glm::mat4 { return this->projectionMatrix; }

auto Camera::updateVectors() -> void
{
	this->target.x = cos(glm::radians(this->yaw));
	this->target.z = sin(glm::radians(this->yaw));
	this->target.y = sin(glm::radians(this->pitch));
	this->target = glm::normalize(this->target);

	this->right = glm::normalize(glm::cross(this->target, glm::vec3(0.0f, 1.0f, 0.0f)));
	this->up = glm::normalize(glm::cross(this->right, this->target));
}

auto Camera::notify() -> void
{
	this->updateVectors();
	for (auto _shader : this->shaders) {
		_shader->updateCamera();
	}
}


auto Camera::registerObserver(Shader* shader) -> void
{
	this->shaders.push_back(shader); this->notify();
}

void Camera::toFront() { this->eye += this->target * Camera::CAMERA_SPEED; }
void Camera::toRight() { this->eye += this->right * Camera::CAMERA_SPEED; }
void Camera::toLeft() { this->eye -= this->right * Camera::CAMERA_SPEED; }
void Camera::toBack() { this->eye -= this->target * Camera::CAMERA_SPEED; }


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
	xOffSet *= Camera::MOUSE_SENSITIVITY;
	yOffSet *= Camera::MOUSE_SENSITIVITY;

	this->yaw += xOffSet;
	this->pitch += yOffSet;

	if (this->pitch > 89.0f) {
		this->pitch = 89.0f;
	}
	if (this->pitch < -89.0f) {
		this->pitch = -89.0f;
	}
}

void Camera::scrollMove(float yOffSet)
{
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
}

