
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>
#include "header/Shader.h";
#include "header/Log.h";
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#include "header/stb_image.h";
#include "header/Texture.h";
#include "header/Camera.h"

using namespace std;

struct PointLight
{
	glm::vec3 position;
	glm::vec3 color;
};

Camera cam(glm::vec3(0.0f, 0.0f, 3.0f));


const glm::vec3 flashOnLightColor(1.0f, 1.0f, 1.0f);
const glm::vec3 flashOffLightColor(0.0f, 0.0f, 0.0f);

glm::vec3 flashLightColor = flashOnLightColor;

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	cam.ScrollCallBack(window, xoffset, yoffset);
}


void processInput(GLFWwindow* window)
{
	//esc ye basıldığında yapılacak işlem tarif edilir
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS) {
		if (flashLightColor == flashOffLightColor) {
			flashLightColor = flashOnLightColor;
		}else {
			flashLightColor = flashOffLightColor;
		}
	}
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos) {

	cam.MouseCallBack(window, xpos, ypos);

}

int main(void) {


	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
	if (window == NULL) {
		cout << "Failed to create GLFW window" << endl;
		glfwTerminate();
		return -1;
	}
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);


	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		Log("Failed to initialize GLAD");
		return -1;
	}

	glViewport(0, 0, 800, 600);
	//Window her resize olduğunda aşağıdaki fonksiyon çağrılacaktır


	Shader lightingShader("resources/shaders/texture.vs", "resources/shaders/texture.fs");
	Shader lightCubeShader("resources/shaders/lightCube.vs", "resources/shaders/lightCube.fs");
	const int numberOfTextures = 2;
	Texture ourTexture(numberOfTextures);
	ourTexture.bindTexture("resources/textures/container2.png", true);
	ourTexture.bindTexture("resources/textures/container2_specular.png", true);
	//ourTexture.bindTexture("resources/textures/matrix.jpg", false);
	ourTexture.use();


	float vertices[] = {
	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,

	-0.5f,  0.5f,  0.5f,  -1.0f,  0.0f,  0.0f,
	-0.5f,  0.5f, -0.5f,  -1.0f,  0.0f,  0.0f,
	-0.5f, -0.5f, -0.5f,  -1.0f,  0.0f,  0.0f,
	-0.5f, -0.5f, -0.5f,  -1.0f,  0.0f,  0.0f,
	-0.5f, -0.5f,  0.5f,  -1.0f,  0.0f,  0.0f,
	-0.5f,  0.5f,  0.5f,  -1.0f,  0.0f,  0.0f,

	 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
	 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
	 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
	-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
	};


	float textureCoords[] = {
	 0.0f, 0.0f, 0.0f,
	 1.0f, 0.0f, 0.0f,
	 1.0f, 1.0f, 0.0f,
	 1.0f, 1.0f, 0.0f,
	 0.0f, 1.0f, 0.0f,
	 0.0f, 0.0f, 0.0f,

	 0.0f, 0.0f, 0.0f,
	 1.0f, 0.0f, 0.0f,
	 1.0f, 1.0f, 0.0f,
	 1.0f, 1.0f, 0.0f,
	 0.0f, 1.0f, 0.0f,
	 0.0f, 0.0f, 0.0f,

	 1.0f, 0.0f, -1.0f,
	 1.0f, 1.0f, -1.0f,
	 0.0f, 1.0f, -1.0f,
	 0.0f, 1.0f, -1.0f,
	 0.0f, 0.0f, -1.0f,
	 1.0f, 0.0f, -1.0f,

	 1.0f, 0.0f, 1.0f,
	 1.0f, 1.0f, 1.0f,
	 0.0f, 1.0f, 1.0f,
	 0.0f, 1.0f, 1.0f,
	 0.0f, 0.0f, 1.0f,
	 1.0f, 0.0f, 1.0f,

	 0.0f, 1.0f, 0.0f,
	 1.0f, 1.0f, 0.0f,
	 1.0f, 0.0f, 0.0f,
	 1.0f, 0.0f, 0.0f,
	 0.0f, 0.0f, 0.0f,
	 0.0f, 1.0f, 0.0f,

	 0.0f, 1.0f, 0.0f,
	 1.0f, 1.0f, 0.0f,
	 1.0f, 0.0f, 0.0f,
	 1.0f, 0.0f, 0.0f,
	 0.0f, 0.0f, 0.0f,
	 0.0f, 1.0f, 0.0f,
	};


	PointLight p1, p2, p3, p4;
	p1.position = glm::vec3(0.7f, 0.2f, 2.0f);
	p1.color = glm::vec3(1.0f, 0.0f, 0.0f);
	p2.position = glm::vec3(2.3f, -3.3f, -4.0f);
	p2.color = glm::vec3(0.0f, 1.0f, 0.0f);
	p3.position = glm::vec3(-4.0f, 2.0f, -12.0f);
	p3.color = glm::vec3(0.0f, 0.0f, 1.0f);
	p4.position = glm::vec3(0.0f, 0.0f, -3.0f);
	p4.color = glm::vec3(1.0f, 1.0f, 0.0f);


	PointLight pointLightPositions[] = { p1,p2,p3,p4
	};

	unsigned int VAO, VBO, TB0;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(VAO);



	//Copy our vertices array in a bufer for OpenGL to use
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);


	//set the vertex attrivbutes pointers

	// color attribute

	// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	//glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));

	glEnableVertexAttribArray(0);
	//glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	glGenBuffers(1, &TB0);
	glBindBuffer(GL_ARRAY_BUFFER, TB0);
	glBufferData(GL_ARRAY_BUFFER, sizeof(textureCoords), textureCoords, GL_STATIC_DRAW);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(1);

	unsigned int lightCubeVAO;
	glGenVertexArrays(1, &lightCubeVAO);
	glBindVertexArray(lightCubeVAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// tell opengl for each sampler to which texture unit it belongs to (only has to be done once)
	// -------------------------------------------------------------------------------------------

	lightingShader.use(); // don't forget to activate/use the shader before setting uniforms!
	// either set it manually like so:


	// or set it via the texture class

	glm::vec3 cubePositions[] = {
glm::vec3(0.0f, 0.0f, 0.0f),
glm::vec3(2.0f, 5.0f, -15.0f),
glm::vec3(-1.5f, -2.2f, -2.5f),
glm::vec3(-3.8f, -2.0f, -12.3f),
glm::vec3(2.4f, -0.4f, -3.5f),
glm::vec3(-1.7f, 3.0f, -7.5f),
glm::vec3(1.3f, -2.0f, -2.5f),
glm::vec3(1.5f, 2.0f, -2.5f),
glm::vec3(1.5f, 0.2f, -1.5f),
glm::vec3(-1.3f, 1.0f, -1.5f)
	};


	glEnable(GL_DEPTH_TEST);


	const float radius = 10.0f;
	// render loop
	// -----------

	float deltaTime = 0.0f; // Time between current frame and last frame
	float lastFrame = 0.0f; // Time of last fram



	glm::mat4 model;
	glm::vec3 lightColor(1.0f, 1.0f, 1.0f);

	glm::vec3 objSpecular = glm::vec3(0.5f) * lightColor;
	float objShinines = 32.0f;


	glm::vec3 lightPos(1.2f, 1.0f, 2.0f);

	glm::vec3 lightAmbient = glm::vec3(0.2f) * lightColor;
	glm::vec3 lightDiffuse = glm::vec3(0.5f) * lightColor;
	glm::vec3 lightSpecular = lightColor;


	while (!glfwWindowShouldClose(window))
	{
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// input
		// -----
		processInput(window);
		cam.dynamicProcessInputs(window, deltaTime);
		float camX = sin(glfwGetTime()) * radius;
		float camZ = cos(glfwGetTime()) * radius;


		//light Source

		lightCubeShader.use();



		lightCubeShader.setMat4fv("view", false, cam.getView());
		lightCubeShader.setMat4fv("projection", false, cam.getCameraPerspective());


		glBindVertexArray(lightCubeVAO);
		for (int i = 0; i < sizeof(pointLightPositions) / sizeof(pointLightPositions[0]); i++) {
			model = glm::mat4(1.0f);
			model = glm::translate(model, pointLightPositions[i].position);
			model = glm::scale(model, glm::vec3(0.2f)); // a smaller cube
			lightCubeShader.setMat4fv("model", false, model);
			lightCubeShader.set3FVector("lightColor", pointLightPositions[i].color);
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}

		lightingShader.use();
		lightingShader.setMat4fv("view", false, cam.getView());
		lightingShader.setMat4fv("projection", false, cam.getCameraPerspective());

		lightingShader.set3FVector("viewPos", cam.getviewPos());

		lightingShader.setInt("material.diffuse", 0);
		lightingShader.setInt("material.specular", 1);
		lightingShader.setInt("material.emission", 2);
		lightingShader.setFloat("material.shininess", objShinines);

		lightingShader.set3FVector("dirLight.direction", -0.2f, -1.0f, -0.3f);
		lightingShader.set3FVector("dirLight.ambient", 0.05f, 0.05f, 0.05f);
		lightingShader.set3FVector("dirLight.diffuse", 0.4f, 0.4f, 0.4f);
		lightingShader.set3FVector("dirLight.specular", 0.5f, 0.5f, 0.5f);

		for (int i = 0; i < sizeof(pointLightPositions) / sizeof(pointLightPositions[0]); i++) {

			auto result = "pointLights[" + std::to_string(i) + "]";
			lightingShader.set3FVector(result + ".position", pointLightPositions[i].position);
			lightingShader.setFloat(result + ".constant", 1.0f);
			lightingShader.setFloat(result + ".linear", 0.09f);
			lightingShader.setFloat(result + ".quadratic", 0.032f);
			lightingShader.set3FVector(result + ".ambient", pointLightPositions[i].color.x * 0.0, pointLightPositions[i].color.y * 0.0, pointLightPositions[i].color.z * 0.0);
			lightingShader.set3FVector(result + ".diffuse", pointLightPositions[i].color.x * 0.5, pointLightPositions[i].color.y * 0.5, pointLightPositions[i].color.z * 0.5); // darken diffuse light a bit
			lightingShader.set3FVector(result + ".specular", pointLightPositions[i].color);
		}

		lightingShader.set3FVector("flashLight.position", cam.getviewPos());
		lightingShader.set3FVector("flashLight.direction", cam.getCamFront());
		lightingShader.set3FVector("flashLight.ambient", 0.0f, 0.0f, 0.0f);
		lightingShader.set3FVector("flashLight.diffuse", flashLightColor);
		lightingShader.set3FVector("flashLight.specular", flashLightColor);
		lightingShader.setFloat("flashLight.constant", 1.0f);
		lightingShader.setFloat("flashLight.linear", 0.09f);
		lightingShader.setFloat("flashLight.quadratic", 0.032f);
		lightingShader.setFloat("flashLight.cutOff", glm::cos(glm::radians(12.5f)));
		lightingShader.setFloat("flashLight.outerCutOff", glm::cos(glm::radians(15.0f)));

		glBindVertexArray(VAO);
		for (unsigned int i = 0; i < sizeof(cubePositions) / sizeof(cubePositions[0]); i++) {
			model = glm::mat4(1.0f);

			model = glm::translate(model, cubePositions[i]);
			float angle = 20.0f * i;
			model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
			lightingShader.setMat4fv("model", false, model);
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteVertexArrays(1, &lightCubeVAO);
	glDeleteBuffers(1, &VBO);


	glfwTerminate();
	return 0;
}

