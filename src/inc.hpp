#pragma once

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>

#include <shader.hpp>
#include <texture.hpp>
#include <lines.hpp>
#include <window.hpp>


constexpr float GRAY = (34.0f / 255.f);
#define GOLD 0.631f, 0.532f, 0.378f, 1.f

typedef unsigned int uint;
typedef unsigned char byte;

#define CHECK() { auto e = glGetError(); if (e != 0) { std::cerr << e << std::endl; abort(); } }