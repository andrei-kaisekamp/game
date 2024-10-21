#include "Sprite.h"
#include "Projectile.h"
#include <vector>


#ifndef EXPLOSION_H
#define EXPLOSION_H

class Explosion : public Sprite {
public:
    Explosion(float positionX, float positionY, vector <GLuint> textures, Magician *magician);
    void drawSprite() override;
    void move();
    bool explosionFinished;
private:
    void updateTexture();
    void setTexture(GLuint texture);
    vector <GLuint> textures;

    float initialPosX, initialPosY;
    Magician *magician;
};


#endif