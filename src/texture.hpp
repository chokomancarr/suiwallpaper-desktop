#pragma once
#include "inc.hpp"

class Texture {
public:
	Texture(const std::string& path);
	~Texture();

	GLuint pointer;
	unsigned int w, h;

	void Draw(const float px, const float py, const float angle, const float size);
};