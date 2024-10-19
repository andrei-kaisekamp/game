#include "Globals.h"

#ifndef SPRITE_H
#define SPRITE_H

class Sprite {
public:
    Sprite();
    Sprite(string filePath);
	GLuint VAO;

	vec3 position;
	vec3 dimensions;
	float angle;
	// Para controle da animação
	int frames;
	int frameID;
	float FPS;
	float lastTime;

    GLuint shader;
    GLuint texture;
	vec2 textureOffset = vec2(0.0, 0.0);

	// Função de inicialização
    virtual void setupSprite(vec3 position, vec3 dimensions, int nFrames, int nAnimations);
    virtual void loadTexture(string filePath, int &imgWidth, int &imgHeight);
    virtual void drawSprite();
    void setupShader();
};

#endif