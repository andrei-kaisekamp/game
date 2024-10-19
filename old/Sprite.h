#include "Globals.h"

#ifndef SPRITE_H
#define SPRITE_H

class Sprite {
public:
    Sprite(vec3 position);
    ~Sprite();

    virtual void setupSprite(int texture);
    GLuint VAO;
    GLuint shader;
	vec3 position;

	float angle;

    //GLuint texture;
	// Para controle da animação
	int frame_id;
private:
	const vec3 dimensions;
	const int frames;
    float FPS;
	float lastTime;
};

#endif