#pragma once
#include <string>
#include <glad/glad.h>

class Texture {
private:
	unsigned int *idList;
	int numberOfTextures;
	int bindingIndex = 0;
public:
	Texture(const int numberOfTextures);

	~Texture();

	void bindTexture(const char* filePath,bool hasAlpha);

	GLuint* getTexttureIdList();

	void use();
};
