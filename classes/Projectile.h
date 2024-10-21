#include "Sprite.h"
#include "Magician.h"
#include <vector>
#include <cmath>

#define M_PI 3.14159265358979323846

#ifndef PROJECTILE_H
#define PROJECTILE_H

class Projectile : public Sprite {
public:
    Projectile(float targetPosX, float targetPosY, vector <GLuint> textures, Magician *magician);
    void drawSprite() override;
    void move();
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