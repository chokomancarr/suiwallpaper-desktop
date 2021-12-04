#pragma once
#include "inc.hpp"

class Shader {
public:
	Shader() : pointer(0xffff), locs({}) {}
	Shader(const std::string& vert, const std::string& frag, const std::initializer_list<std::string> uniforms);
	~Shader();

	bool operator !() {
		return pointer == 0xffff;
	}

	GLuint pointer;
	std::vector<int> locs;
};