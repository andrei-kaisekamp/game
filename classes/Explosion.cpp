#include "Explosion.h"

Explosion::Explosion(float positionX, float positionY, vector <GLuint> textures, Magician *magician){
    this->initialPosX = positionX;
    this->initialPosY = positionY + 25;

    this->FPS = 10.0;
    this->textures = textures;

    setupShader();
    setTexture(textures[0]);

    setupSprite(
        vec3((this->initialPosX), (this->initialPosY), 1.0), //position
        vec3(300, 300, 1.0f),    //dimension
        1, 1                     //frames and animation
    );

    this->explosionFinished = false;
    this->frameID = 0;
    this->magician = magician;

}

void Explosion::setTexture(GLuint texture) {
    this->texture = texture;
}

void Explosion::move() {
    if(characterIsMoving){
        if(magician->isFacingRight)
            position.x -= 1 + (static_cast<float>(7)/2);
        else
            position.x += 1 + (static_cast<float>(7)/2);
    }
}

void Explosion::drawSprite() {
    updateTexture();
    Sprite::drawSprite();
};

void Explosion::updateTexture() {
	float currentTime = glfwGetTime();
	float deltaTime = currentTime - this->lastTime;

	if (deltaTime >= 1.0 / this->FPS) {
        setTexture(textures[frameID]);
		this->lastTime = currentTime;
        frameID += 1;
        if(frameID == 10){
            explosionFinished = true;
            frameID = 0;
        }
	}	
};