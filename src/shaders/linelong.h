#pragma once
#include "inc.hpp"

namespace glsl {
	const std::string lineL_v = R"(
		#version 330 core

		uniform vec2 reso;
		uniform vec2 center;
		uniform int count;
		uniform float off;
		uniform float len;

		void main() {
			float isout = mod(gl_VertexID, 2);
			float angle = off + (gl_VertexID - isout) * 2 * 3.14159f / count;

			vec2 p = vec2(center.x, center.y) + vec2(sin(angle) * reso.y / reso.x, cos(angle)) * len * isout;

			gl_Position.xy = p;
			gl_Position.z = 0;
			gl_Position.w = 1.0;
		}
	)";

	const std::string lineL_f = R"(
		#version 330 core

		uniform vec4 col;

		out vec4 color;

		void main() {
			color = col;
		}
	)";
}