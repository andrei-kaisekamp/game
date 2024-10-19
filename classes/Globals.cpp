#include "Globals.h"

//tela:
const GLuint WIDTH = 960;
const GLuint HEIGHT = 540;

//sprites:
mat4 projection = ortho(0.0f, (static_cast<float>(WIDTH)), 0.0f, (static_cast<float>(HEIGHT)), -1.0f, 1.0f);

//shaders:
const GLchar *vertexShaderSource = 
    "#version 400\n"
	"layout (location = 0) in vec3 position;\n"
	"layout (location = 1) in vec2 texc;\n"
	"uniform mat4 projection;\n"
	"uniform mat4 model;\n"
	"out vec2 texCoord;\n"
	"void main()\n"
	"{\n"
	"gl_Position = projection * model * vec4(position.x, position.y, position.z, 1.0);\n"
	"texCoord = vec2(texc.s, 1.0 - texc.t);\n"
	"}\0";

const GLchar *fragmentShaderSource = 
    "#version 400\n"
	"in vec2 texCoord;\n"
	"uniform sampler2D texBuffer;\n"
	"uniform vec2 offsetTex;\n"
	"out vec4 color;\n"
	"void main()\n"
	"{\n"
	"color = texture(texBuffer, texCoord + offsetTex);\n"
	"}\n\0";
