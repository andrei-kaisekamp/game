#include "Background.h"

Background::Background() {};
Background::Background(GLuint texture, int width, int height, float layer){
    setupShader();
    setupSprite(
        vec3(
            (static_cast<float>(WIDTH)/2),     
            (static_cast<float>(HEIGHT) / 2), 
            1.0
        ), 
        vec3(
            static_cast<float>(width*2)*WIDTH/width, 
            static_cast<float>(height)*HEIGHT/height, 
            1.0f), 1, 1
    );
    this->layer = layer;
    this->isFacingRight = true;
    this->texture = texture;
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
    Sprite::drawSprite();
};