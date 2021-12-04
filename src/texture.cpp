#include <texture.hpp>
#include "lodepng.h"
#include "shaders/tex.h"

namespace {
	void FlipY(std::vector<unsigned char>& data, unsigned int w, unsigned int h) {
		for (int a = 0; a < h / 2; ++a) {
			std::vector<unsigned char> tmp(w * 4);
			memcpy(&tmp[0], &data[a * w * 4], w * 4);
			memcpy(&data[a * w * 4], &data[(h - a - 1) * w * 4], w * 4);
			memcpy(&data[(h - a - 1) * w * 4], &tmp[0], w * 4);
		}
	}
}

Texture::Texture(const std::string& path) {
	std::ifstream strm(path, std::ios::binary | std::ios::ate);
	const auto len = strm.tellg();
	std::vector<unsigned char> mem(len), data = {};
	strm.seekg(0);
	strm.read((char*)mem.data(), len);
	lodepng::decode(data, w, h, mem);
	FlipY(data, w, h);

	glGenTextures(1, &pointer);
	glBindTexture(GL_TEXTURE_2D, pointer);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, data.data());
	glGenerateMipmap(GL_TEXTURE_2D);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, 5);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBindTexture(GL_TEXTURE_2D, 0);
}

Texture::~Texture() {
	glDeleteTextures(1, &pointer);
}

void Texture::Draw(const float px, const float py, const float angle, const float size) {
	static Shader shad(glsl::tex_v, glsl::tex_f, {
		"reso", "center", "angle", "sz", "tex"
		});
	static GLuint vao = 0;
	if (!vao) {
		glCreateVertexArrays(1, &vao);
	}

	glUseProgram(shad.pointer);
	glUniform2f(shad.locs[0], Window::w, Window::h);
	glUniform2f(shad.locs[1], px, py);
	glUniform1f(shad.locs[2], angle);
	glUniform1f(shad.locs[3], size);
	glUniform1i(shad.locs[4], 0);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, pointer);

	glBindVertexArray(vao);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

	glUseProgram(0);
}