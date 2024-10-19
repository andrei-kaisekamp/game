#include <Sprite.h>

#ifndef BACKGROUND_H
#define BACKGROUND_H

class Background : public Sprite {
public:
    Background(vec3 position);
    void setupSprite(int texture);
private:
    GLuint texture;
};



#endif