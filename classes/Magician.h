#include "Sprite.h"

#ifndef MAGICIAN_H
#define MAGICIAN_H

class Magician : public Sprite {
public:
    Magician(string filePath);
    void moveLeft();
    void moveRight();
    void jump();
    void drawSprite() override;
    void idle();
    bool isJumping;
private:
    bool firstJumpLoop;
    float jumpSpeed;
    void updateFrame();
    void moving();
};


#endif