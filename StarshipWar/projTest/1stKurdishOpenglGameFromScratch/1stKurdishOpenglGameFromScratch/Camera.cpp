#include "Camera.h"

Camera::Camera(){}

Camera::Camera(glm::vec3 startPosition, glm::vec3 startUp, GLfloat startYaw, GLfloat startPitch, GLfloat startMoveSpeed ,GLfloat startTurnSpeed)
{
	position = startPosition;
	worldUp = startUp;
	yaw = startYaw;
	pitch = startPitch;
	front = glm::vec3(0.0f,0.0f,-1.0f);
	moveSpeed = startMoveSpeed;
	turnSpeed = startTurnSpeed;

	Update();
}
/////////////
void Camera::keyControl(bool* keys, GLfloat deltaTime)
{
	//delta time is toslow down frames in games otherwise have 10k frame per second
	GLfloat velocity = moveSpeed* deltaTime;

	if (keys[GLFW_KEY_W])
	{
		position += front * velocity;
	}
	if (keys[GLFW_KEY_S])
	{
		position  -= front * velocity;
	}
	if (keys[GLFW_KEY_A])
	{
		position -= right * velocity;
	}
	if (keys[GLFW_KEY_D])
	{
		position += right * velocity;
	}
}

void Camera::mouseControl(GLfloat Xchange, GLfloat Ychange)
{
	Xchange *= turnSpeed;
	Ychange *= turnSpeed;
	yaw += Xchange;
	pitch += Ychange;

	if (pitch > 89.0f) 
	{
		pitch = 89.0f;

	}
	if(pitch < - 89.0f)
	{
		pitch = -89.0f;
	}

	Update();
}

glm::mat4 Camera::calculateViewMatrix()
{

	return glm::lookAt(position, position + front, up); //lookAt functioneka wata bnwara :)


}
//////////////
///vec3 for shininess and stuff specular lighting 
glm::vec3 Camera::getCameraPosition()
{
	return position; // hold that position and pass it into our shader , now we go to shader vert ...
}
//////////////
glm::vec3 Camera::getCameraDirection()
{
	return glm::normalize(front);
}
//////////////
void Camera::Update()
{
	front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	front.y = sin(glm::radians(pitch));
	front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	front = glm::normalize(front);

	right = glm::normalize(glm::cross(front, worldUp));
	up = glm::normalize(glm::cross(right, front));
}

Camera::~Camera()
{
}
