#include "Globals.h"
#include "Sprite.h"

#ifndef MAGICIAN_H
#define MAGICIAN_H

class Magician : public Sprite {
public:
    Magician();
    //Magician(string filePath);
    Magician(Texture textures);
    void moveLeft();
    void moveRight();
    void jump();
    void drawSprite() override;
    void idle();
    bool isJumping;
    float getPosX() {return this->position.x;};
    float getPosY() {return this->position.y;};
private:
    bool firstJumpLoop;
    float jumpSpeed;
    void updateFrame();
    void moving();
    Texture textures;
};


#endif