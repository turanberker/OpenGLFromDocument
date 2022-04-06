
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

using namespace std;

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window)
{
	//esc ye basıldığında yapılacak işlem tarif edilir
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

void determineX(GLFWwindow* window, float& x , float& y) {
	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
		x -= 0.005f;
	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
		x +=  0.005f;
	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
		y += 0.005f;
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
		y -= 0.005f;

	if (x > 0.5) {
		x = 0.5;
	}	else if (x < -0.5) {
		x = -0.5;
	}

	if (y > 0.5) {
		y = 0.5;
	}
	else if (y < -0.5) {
		y = -0.5;
	}
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
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		Log("Failed to initialize GLAD");
		return -1;
	}

	glViewport(0, 0, 800, 600);
	//Window her resize olduğunda aşağıdaki fonksiyon çağrılacaktır


	Shader ourShader("resources/shaders/texture.vs", "resources/shaders/texture.fs");
	Texture ourTexture(numberOfTextures);
	ourTexture.bindTexture("resources/textures/container.jpg",false);
	ourTexture.bindTexture("resources/textures/awesomeface.png",true);	
	

	float vertices[] = {
		// positions // colors // texture coords
		0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, // top right
		0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, // bottom right
		-0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, // bottom left
		-0.5f, 0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f // top left
	};


	unsigned int indices[] = {
	  0, 1, 3, // first triangle
	  1, 2, 3  // second triangle
	};

	unsigned int VAO, VBO, EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(VAO);

	//Copy our vertices array in a bufer for OpenGL to use
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	//copy our index array in a element buffer for OpenGL to use
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	
	//set the vertex attrivbutes pointers
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	// color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float),(void*)(6 * sizeof(float)));
	
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	// tell opengl for each sampler to which texture unit it belongs to (only has to be done once)
	// -------------------------------------------------------------------------------------------
	ourShader.use(); // don't forget to activate/use the shader before setting uniforms!
	// either set it manually like so:
	for (int i = 0; i < numberOfTextures; i++) {
		std::string texture= "texture";
		texture = texture +std::to_string(i + 1);
		ourShader.setInt(texture, i);
	}
	// or set it via the texture class
	
	glm::mat4 trans = glm::mat4(1.0f);
	float angle = (float)glfwGetTime();
	trans = glm::rotate(trans, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	
	glm::mat4 view = glm::mat4(1.0f);
	// note that we’re translating the scene in the reverse direction
	view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
	
	glm::mat4 projection;
	projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f,100.0f);

	float x = 0.0;
	float y = 0.0;
	// render loop
	// -----------
	while (!glfwWindowShouldClose(window))
	{

		determineX(window, x,y);
		
	
		glm::mat4 itr = glm::mat4(1.0f);
		itr=glm::translate(itr, glm::vec3(x, y, 0.0f));
		// input
		// -----
		processInput(window);

		// render
		// ------
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		
		ourTexture.use();
		ourShader.setMat4fv("rotation", false ,trans);
		ourShader.setMat4fv("iteration", false, itr);
		ourShader.setMat4fv("view", false, view);
		ourShader.setMat4fv("projection", false, projection);
		// render container
		//ourShader.use();
		
		glBindVertexArray(VAO);
		
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		// -------------------------------------------------------------------------------
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);


	glfwTerminate();
	return 0;
}

