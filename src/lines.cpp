#include "inc.hpp"
#include "shaders/linelong.h"
#include "shaders/circle.h"

namespace {
	GLuint vao = 0;
}

void Lines::DrawLongs(const float px, const float py, const float angle, const float len) {
	static Shader shad(glsl::lineL_v, glsl::lineL_f, {
		"reso", "center", "count", "off", "len", "col"
	});
	if (!vao) {
		glCreateVertexArrays(1, &vao);
	}

	glUseProgram(shad.pointer);
	glUniform2f(shad.locs[0], Window::w, Window::h);
	glUniform2f(shad.locs[1], px, py);
	glUniform1i(shad.locs[2], 36);
	glUniform1f(shad.locs[3], angle);
	glUniform1f(shad.locs[4], len);
	glUniform4f(shad.locs[5], GOLD);

	glLineWidth(0.5f);
	glBindVertexArray(vao);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glDrawArrays(GL_LINES, 0, 72);

	glUseProgram(0);

}

void Lines::DrawCircle(const float px, const float py, const float r, const int n) {
	static Shader shad(glsl::circle_v, glsl::circle_f, {
		"reso", "center", "count", "rad", "col"
		});
	if (!vao) {
		glCreateVertexArrays(1, &vao);
	}

	glUseProgram(shad.pointer);
	glUniform2f(shad.locs[0], Window::w, Window::h);
	glUniform2f(shad.locs[1], px, py);
	glUniform1i(shad.locs[2], n);
	glUniform1f(shad.locs[3], r);
	glUniform4f(shad.locs[4], GOLD);

	glLineWidth(0.5f);
	glBindVertexArray(vao);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glDrawArrays(GL_LINE_STRIP, 0, n + 1);

	glUseProgram(0);
}