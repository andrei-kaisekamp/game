#include "Background.h"

Background::Background() {};
Background::Background(string filePath, float layer){
    int imgWidth, imgHeight;
    setupShader();
    loadTexture(filePath, imgWidth, imgHeight);

    setupSprite(
        vec3(
            (static_cast<float>(WIDTH)/2),     
            (static_cast<float>(HEIGHT) / 2), 
            1.0
        ), 
        vec3(
            static_cast<float>(imgWidth*2)*WIDTH/imgWidth, 
            static_cast<float>(imgHeight)*HEIGHT/imgHeight, 
            1.0f), 1, 1
    );
    this->layer = layer;
    this->isFacingRight = true;
}

void Background::moveLeft() {
    this->position.x += defaultSpeed + (layer/2);
    if(this->position.x >= 960.0)
        this->position.x = 0.0;
}

void Background::moveRight() {
    this->position.x -= defaultSpeed + (layer/2);
    if(this->position.x <= 0.0)
        this->position.x = 960.0;
}

void Background::moveSky() {
    this->position.x -= skySpeed * layer;

    if(this->position.x < 0.0)
        this->position.x = 960.0;
    
    if(this->position.x > 960.0)
        this->position.x = 0.0;
}


void Background::drawSprite() {
    //updateFrame();
    Sprite::drawSprite();
};