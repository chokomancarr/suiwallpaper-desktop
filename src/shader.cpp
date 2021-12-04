#include "shader.hpp"

namespace {
	GLuint LoadShader(GLenum shaderType, std::string source) {
		int compile_result = 0;
		GLuint res = glCreateShader(shaderType);
		const char* shader_code_ptr = source.c_str();
		const int shader_code_size = source.size();
		glShaderSource(res, 1, &shader_code_ptr, &shader_code_size);
		glCompileShader(res);
		glGetShaderiv(res, GL_COMPILE_STATUS, &compile_result);
		if (!compile_result) {
			int info_log_length = 0;
			glGetShaderiv(res, GL_INFO_LOG_LENGTH, &info_log_length);
			std::vector<char> program_log(info_log_length);
			glGetShaderInfoLog(res, info_log_length, NULL, &program_log[0]);
			std::cerr << program_log.data() << std::endl;
			abort();
		}
		return res;
	}
}

Shader::Shader(const std::string& vert, const std::string& frag, const std::initializer_list<std::string> uniforms)
		: Shader() {
	auto vs = LoadShader(GL_VERTEX_SHADER, vert);
	auto fs = LoadShader(GL_FRAGMENT_SHADER, frag);
	pointer = glCreateProgram();
	glAttachShader(pointer, vs);
	glAttachShader(pointer, fs);

	int link_result = 0;
	glLinkProgram(pointer);
	glGetProgramiv(pointer, GL_LINK_STATUS, &link_result);
	assert(link_result > 0);

	glDetachShader(pointer, vs);
	glDetachShader(pointer, fs);
	glDeleteShader(vs);
	glDeleteShader(fs);

	for (auto& u : uniforms) {
		locs.push_back(glGetUniformLocation(pointer, u.c_str()));
	}
}

Shader::~Shader() {
	if (pointer != 0xffff) {
		glDeleteProgram(pointer);
		pointer = 0;
	}
}