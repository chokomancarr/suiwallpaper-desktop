#pragma once
#include "inc.hpp"

namespace glsl {
	const std::string tex_v = R"(
		#version 330 core

		uniform vec2 reso;
		uniform vec2 center;
		uniform float angle;
		uniform float sz;

		out vec2 uv;

		void main() {
			float px0 = ((gl_VertexID > 0 && gl_VertexID < 3) ? 1 : 0);
			float py0 = ((gl_VertexID > 1) ? 1 : 0);

			vec2 p = vec2(px0, py0) * 2 - 1;
			float cs = cos(angle);
			float ss = sin(angle);
			p = vec2(cs * p.x + ss * p.y, cs * p.y - ss * p.x) * sz;
			p.x *= reso.y / reso.x;
			p += center;

			gl_Position.xy = p;
			gl_Position.z = 0;
			gl_Position.w = 1.0;
			uv = vec2(px0, py0);
		}
	)";

	const std::string tex_f = R"(
		#version 330 core

		in vec2 uv;

		uniform sampler2D tex;

		out vec4 color;

		void main() {
			color = texture(tex, uv);
		}
	)";
}