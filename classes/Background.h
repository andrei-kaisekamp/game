#include "Sprite.h"

#ifndef BACKGROUND_H
#define BACKGROUND_H

class Background : public Sprite {
public:
    Background();
    Background(GLuint texture, int width, int height, float layer);
    void drawSprite() override;
    void moveRight();
    void moveLeft();
    void moveSky();
private:
    float layer;
};


#endif