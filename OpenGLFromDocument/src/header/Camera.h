#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>

class Camera {
private:
	float fov = 45;
	float yaw = -90.0f;
	float pitch = 0.0f;
	float lastX = 400, lastY = 300;
	bool firstMouse = true;
	glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
	glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 yukari = glm::vec3(0.0f, 1.0f, 0.0f);

	

public:
	Camera(glm::vec3 cameraPos);
	void MouseCallBack(GLFWwindow* window, double xpos, double ypos);
	void ScrollCallBack(GLFWwindow* window, double xoffset, double yoffset);
	void dynamicProcessInputs(GLFWwindow* window, float deltaTime);
	glm::mat4 CameraPerspective();
	glm::mat4 getView();
};
