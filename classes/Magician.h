#include "Sprite.h"

#ifndef MAGICIAN_H
#define MAGICIAN_H

class Magician : public Sprite {
public:
    Magician(string filePath);
    void moveLeft();
    void moveRight();
    void drawSprite() override;
private:
    const int speed = 5;
    void updateFrame();
};


#endif