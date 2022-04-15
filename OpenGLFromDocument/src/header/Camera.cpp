#include "Camera.h"

void Camera::ScrollCallBack(GLFWwindow* window, double xoffset, double yoffset)
{
	this->fov -= (float)yoffset;
	if (this->fov < 1.0f)
		this->fov = 1.0f;
	if (this->fov > 45.0f)
		this->fov = 45.0f;
	
	this->cameraPerspective = glm::perspective(glm::radians(this->fov), 800.0f / 600.0f, 0.1f, 100.0f);
}

void Camera::dynamicProcessInputs(GLFWwindow* window, float deltaTime)
{
	const float cameraSpeed = 2.5f * deltaTime; // adjust accordingly
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		cameraPos += cameraSpeed * cameraFront;
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		cameraPos -= cameraSpeed * cameraFront;
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		cameraPos -= glm::normalize(glm::cross(cameraFront, yukari)) * cameraSpeed;
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		cameraPos += glm::normalize(glm::cross(cameraFront, yukari)) * cameraSpeed;
	if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS)
		cameraPos += glm::normalize(yukari) * cameraSpeed;
	if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS)
		cameraPos -= glm::normalize(yukari) * cameraSpeed;
	//cameraPos.y = 0.0f;
	cameraView = glm::lookAt(cameraPos, cameraPos + cameraFront, yukari);
}

glm::mat4& Camera::getCameraPerspective()
{
	return cameraPerspective;
}

glm::mat4& Camera::getView()
{
	return cameraView;

}

glm::vec3& Camera::getviewPos()
{
	return cameraPos;
}

Camera::Camera(glm::vec3 cameraPos)
{
	cameraPerspective = glm::perspective(glm::radians(fov), 800.0f / 600.0f, 0.1f, 100.0f);
	cameraView = glm::lookAt(cameraPos, cameraPos + cameraFront, yukari);
	this->cameraPos = cameraPos;
}

void Camera::MouseCallBack(GLFWwindow* window, double xpos, double ypos) {
	if (firstMouse) // initially set to true
	{
		this->lastX = xpos;
		this->lastY = ypos;
		this->firstMouse = false;
	}
	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos; // reversed: y ranges bottom to top
	lastX = xpos;
	lastY = ypos;
	const float sensitivity = 0.1f;
	xoffset *= sensitivity;
	yoffset *= sensitivity;

	yaw += xoffset;
	pitch += yoffset;

	if (pitch > 89.0f)
		pitch = 89.0f;
	if (pitch < -89.0f)
		pitch = -89.0f;

	glm::vec3 direction;
	direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	direction.y = sin(glm::radians(pitch));
	direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	this->cameraFront = glm::normalize(direction);
	cameraView = glm::lookAt(cameraPos, cameraPos + cameraFront, yukari);
}