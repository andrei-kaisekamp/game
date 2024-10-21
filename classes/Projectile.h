#include "Sprite.h"
#include "Magician.h"
#include <vector>
#include <cmath>

#ifndef PROJECTILE_H
#define PROJECTILE_H

class Projectile : public Sprite {
public:
    Projectile(float targetPosX, float targetPosY, vector <GLuint> textures, Magician *magician);
    void drawSprite() override;
    void move();
    float getPosX() {return this->position.x;};
    float getPosY() {return this->position.y;};
    bool isOutOfRange;
private:
    void updateTexture();
    void setTexture(GLuint texture);
    void calculateDirections();
    vector <GLuint> textures;

    float initialPosX, initialPosY, targetPosX, targetPosY, directionX, directionY;
    float defaultSpeed, xSpeed, ySpeed;
    Magician *magician;
};


#endif