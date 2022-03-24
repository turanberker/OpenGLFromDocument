#pragma once
#include <string>


class Texture {
private:
	unsigned int ID;
public:
	Texture(const char* filePath);

	~Texture();

	void use();
};
