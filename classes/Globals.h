#include <iostream>
#include <string>
#include <assert.h>
// GLAD
#include <glad/glad.h>
// GLFW
#include <GLFW/glfw3.h>
// GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace glm;

// STB_IMAGE
#include "stb_image.h"

using namespace std;


#ifndef GLOBALS_H
#define GLOBALS_H

//tela:
extern const GLuint WIDTH;
extern const GLuint HEIGHT;

//sprites:
extern mat4 projection;

//shaders:
extern const GLchar *vertexShaderSource;
extern const GLchar *fragmentShaderSource;

#endif