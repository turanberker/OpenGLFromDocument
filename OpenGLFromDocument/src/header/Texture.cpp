#include "Texture.h"
#include "stb_image.h"
#include <glad/glad.h>
#include <iostream>

Texture::Texture(const int numberOfTextures) {
	this->numberOfTextures = numberOfTextures;
	this->idList = new unsigned int[numberOfTextures];

	// set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

void Texture::bindTexture(const char* filePath, bool hasAlpha) {

	glGenTextures(bindingIndex+1, &idList[bindingIndex]);
	glBindTexture(GL_TEXTURE_2D, idList[bindingIndex]);

	// load image, create texture and generate mipmaps
	int width, height, nrChannels;
	stbi_set_flip_vertically_on_load(true);
	// The FileSystem::getPath(...) is part of the GitHub repository so we can find files on any IDE/platform; replace it with your own image path.
	unsigned char* data = stbi_load(filePath, &width, &height, &nrChannels, 0);
	if (data)
	{
		if (hasAlpha) {
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		}
		else {
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		}		
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data);
//	glActiveTexture(GL_TEXTURE0);
//	glBindTexture(GL_TEXTURE0, ID);

	bindingIndex++;
}

Texture::~Texture()
{
	//delete[] idList;
}

void Texture::use()
{
	for (int i = 0; i < numberOfTextures; i++) {
		glActiveTexture(GL_TEXTURE0+i);
		glBindTexture(GL_TEXTURE_2D, idList[i]);
	}
	// bind Texture

//	glActiveTexture(GL_TEXTURE0 );
//	glBindTexture(GL_TEXTURE_2D, idList[0]);

//	glActiveTexture(GL_TEXTURE1);
//	glBindTexture(GL_TEXTURE_2D, idList[1]);
	
}

GLuint* Texture::getTexttureIdList() {
	return this->idList;
}
