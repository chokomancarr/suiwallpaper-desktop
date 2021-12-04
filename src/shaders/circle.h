#pragma once
#include "inc.hpp"

namespace glsl {
	const std::string circle_v = R"(
		#version 330 core

		uniform vec2 reso;
		uniform vec2 center;
		uniform int count;
		uniform float rad;

		void main() {
			float angle = gl_VertexID * 2 * 3.14159f / count;

			vec2 p = vec2(sin(angle), cos(angle)) * rad;
			p = vec2(center.x, center.y) + vec2(p.x * reso.y / reso.x, p.y);

			gl_Position.xy = p;
			gl_Position.z = 0;
			gl_Position.w = 1.0;
		}
	)";

	const std::string circle_f = R"(
		#version 330 core

		uniform vec4 col;

		out vec4 color;

		void main() {
			color = col;
		}
	)";
}