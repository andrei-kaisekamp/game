#include "Sprite.h"

Sprite::Sprite() {}

Sprite::Sprite(string filePath) {
    int imgWidth, imgHeight;
    setupShader();
    loadTexture(filePath, imgWidth, imgHeight);
    //setupSprite()
}

void Sprite::setupSprite(vec3 position, vec3 dimensions, int nFrames, int nAnimations)
{
	this->dimensions = dimensions;
	this->position   = position;
	this->frames     = nFrames;
	this->FPS        = 12.0;
	this->lastTime   = 0.0;
	this->frameID    = 0;

    glUseProgram(this->shader);

	float widthLimit = 1.0 / (float)frames;
	GLfloat vertices[] = {
		// x     y    z    s     	   t
		-0.5, -0.5, 0.0, 0.0,        0.0,  // V0
		-0.5,  0.5, 0.0, 0.0,        1.0,  // V1
		 0.5, -0.5, 0.0, widthLimit, 0.0,  // V2
		 0.5,  0.5, 0.0, widthLimit, 1.0   // V3

	};

	GLuint VBO, VAO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	// Atributo 0 - Posição - x, y, z
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid *)0);
	glEnableVertexAttribArray(0);

	// Atributo 1 - Coordenadas de textura - s, t
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid *)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	this->VAO = VAO;
}

void Sprite::loadTexture(string filePath, int &imgWidth, int &imgHeight)
{
	GLuint texture;

	// Gera o identificador da textura na memória
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	// Configurando o wrapping da textura
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// Configurando o filtering de minificação e magnificação da textura
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	// Carregamento da imagem da textura
	int nrChannels;
	unsigned char *data = stbi_load(filePath.c_str(), &imgWidth, &imgHeight, &nrChannels, 0);

	if (data)
	{
		if (nrChannels == 3) // jpg, bmp
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, imgWidth, imgHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		}
		else // png
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imgWidth, imgHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		}
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << filePath << std::endl;
	}

	this->texture = texture;
}

void Sprite::drawSprite()
{
    glUseProgram(this->shader);
	glBindVertexArray(this->VAO);
	glBindTexture(GL_TEXTURE_2D, this->texture);

	// Matriz de modelo - Tranformações na geometria, nos objetos
	mat4 model = mat4(1); // matriz identidade
	model = translate(model, this->position);
	model = rotate(model, this->angle, vec3(0.0, 0.0, 1.0));


	// Condição para espelhar o sprite no eixo X
    vec3 scaleFactors = this->dimensions;
    if (!isFacingRight) {
        // Espelhar horizontalmente, aplicando escala negativa no eixo X
        scaleFactors.x *= -1.0f;
    }
    
    // Aplicar a escala com os valores ajustados
    model = scale(model, scaleFactors);

	glUniformMatrix4fv(glGetUniformLocation(this->shader, "model"), 1, GL_FALSE, value_ptr(model));
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	glBindVertexArray(0);
}

void Sprite::setupShader() {
    // Vertex shader
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);
	// Checando erros de compilação (exibição via log no terminal)
	GLint success;
	GLchar infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n"
				  << infoLog << std::endl;
	}
	// Fragment shader
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);
	// Checando erros de compilação (exibição via log no terminal)
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n"
				  << infoLog << std::endl;
	}
	// Linkando os shaders e criando o identificador do programa de shader
	GLuint shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	// Checando por erros de linkagem
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n"
				  << infoLog << std::endl;
	}
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	this->shader = shaderProgram;

    glUseProgram(this->shader);
	glUniform1i(glGetUniformLocation(this->shader, "texBuffer"), 0);
    glUniformMatrix4fv(glGetUniformLocation(this->shader, "projection"), 1, GL_FALSE, value_ptr(projection));
}