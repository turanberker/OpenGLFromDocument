﻿
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

Camera cam(glm::vec3(0.0f, 0.0f, 3.0f));

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
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos) {

	cam.MouseCallBack(window, xpos, ypos);

}

int main(void) {

	const int numberOfTextures = 2;
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


	Shader cubeShader("resources/shaders/texture.vs", "resources/shaders/texture.fs");
	Shader lightCubeShader("resources/shaders/lightCube.vs", "resources/shaders/lightCube.fs");
	Texture ourTexture(numberOfTextures);
	ourTexture.bindTexture("resources/textures/container.jpg", false);
	//ourTexture.bindTexture("resources/textures/awesomeface.png", true);


	float vertices[] = {
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 0.0f,  0.0f, -1.0f,
	 0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f,  0.0f, -1.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 0.0f,  0.0f, -1.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 0.0f,  0.0f, -1.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 0.0f,  0.0f, -1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 0.0f,  0.0f, -1.0f,

	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 0.0f,  0.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 0.0f,  0.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 0.0f,  0.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 0.0f,  0.0f, 1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 0.0f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 0.0f,  0.0f, 1.0f,

	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f, -1.0f,  0.0f,  0.0f,
	-0.5f,  0.5f, -0.5f,  1.0f, 1.0f, -1.0f,  0.0f,  0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f, -1.0f,  0.0f,  0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f, -1.0f,  0.0f,  0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f, -1.0f,  0.0f,  0.0f,
	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f, -1.0f,  0.0f,  0.0f,

	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 1.0f,  0.0f,  0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 1.0f,  0.0f,  0.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 1.0f,  0.0f,  0.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 1.0f,  0.0f,  0.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 1.0f,  0.0f,  0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 1.0f,  0.0f,  0.0f,

	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f, -1.0f,  0.0f,
	 0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 0.0f, -1.0f,  0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 0.0f, -1.0f,  0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 0.0f, -1.0f,  0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 0.0f, -1.0f,  0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f, -1.0f,  0.0f,

	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 0.0f,  1.0f,  0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 0.0f,  1.0f,  0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.0f,  1.0f,  0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.0f,  1.0f,  0.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 0.0f,  1.0f,  0.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 0.0f,  1.0f,  0.0f
	};


	unsigned int VAO, VBO;
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
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(5 * sizeof(float)));

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);



	unsigned int lightCubeVAO;
	glGenVertexArrays(1, &lightCubeVAO);
	glBindVertexArray(lightCubeVAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// tell opengl for each sampler to which texture unit it belongs to (only has to be done once)
	// -------------------------------------------------------------------------------------------

	cubeShader.use(); // don't forget to activate/use the shader before setting uniforms!
	// either set it manually like so:
	for (int i = 0; i < numberOfTextures; i++) {
		std::string texture = "texture";
		texture = texture + std::to_string(i + 1);
		cubeShader.setInt(texture, i);
	}
	// or set it via the texture class

	glm::vec3 cubePositions[] = {
glm::vec3(0.0f, 0.0f, 0.0f),
//glm::vec3(2.0f, 5.0f, -15.0f),
//glm::vec3(-1.5f, -2.2f, -2.5f),
//glm::vec3(-3.8f, -2.0f, -12.3f),
//glm::vec3(2.4f, -0.4f, -3.5f),
//glm::vec3(-1.7f, 3.0f, -7.5f),
//glm::vec3(1.3f, -2.0f, -2.5f),
//glm::vec3(1.5f, 2.0f, -2.5f),
//glm::vec3(1.5f, 0.2f, -1.5f),
//glm::vec3(-1.3f, 1.0f, -1.5f)
	};


	glEnable(GL_DEPTH_TEST);


	const float radius = 10.0f;
	// render loop
	// -----------

	float deltaTime = 0.0f; // Time between current frame and last frame
	float lastFrame = 0.0f; // Time of last fram


	glm::vec3 lightPos(3.0f, 2.0f, 2.0f);
	glm::mat4 model;

	glm::vec3 lightColor(1.0f, 1.0f, 1.0f);
	glm::vec3 objectColor(1.0f, 0.5f, 0.31f);

	glm::vec3 ambient(1.0f, 0.5f, 0.31f);
	glm::vec3 diffuse(1.0f, 0.5f, 0.31f);
	glm::vec3 specular(0.5f, 0.5f, 0.5f);

	glm::vec3 lightAmbient = glm::vec3(0.2f) * lightColor;
	glm::vec3 lightDiffuse = glm::vec3(0.5f) * lightColor;
	glm::vec3 lightSpecular= lightColor;
	float shinines=32.0f;

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
		model = glm::mat4(1.0f);
		model = glm::translate(model, lightPos);
		model = glm::scale(model, glm::vec3(0.2f)); // a smaller cube
		lightCubeShader.use();

		lightCubeShader.setMat4fv("model", false, model);
		lightCubeShader.set3FVector("lightColor", lightColor);
		lightCubeShader.setMat4fv("view", false, cam.getView());
		lightCubeShader.setMat4fv("projection", false, cam.getCameraPerspective());
		glBindVertexArray(lightCubeVAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);

		cubeShader.use();
		cubeShader.setMat4fv("view", false, cam.getView());
		cubeShader.setMat4fv("projection", false, cam.getCameraPerspective());
		
		cubeShader.set3FVector("viewPos", cam.getviewPos());

		cubeShader.set3FVector("material.ambient",ambient);
		cubeShader.set3FVector("material.diffuse", diffuse);
		cubeShader.set3FVector("material.specular", specular);
		cubeShader.setFloat("material.shininess", shinines);

		cubeShader.set3FVector("light.position", lightPos);
		cubeShader.set3FVector("light.ambient", lightAmbient);
		cubeShader.set3FVector("light.diffuse", lightDiffuse); // darken diffuse light a bit
		cubeShader.set3FVector("light.specular", lightSpecular);

		// render container

		glBindVertexArray(VAO);
		for (unsigned int i = 0; i < sizeof(cubePositions) / sizeof(cubePositions[0]); i++) {
			model = glm::mat4(1.0f);

			model = glm::translate(model, cubePositions[i]);
			cubeShader.setMat4fv("model", false, model);
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

