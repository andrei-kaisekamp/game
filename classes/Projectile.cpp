#include "Projectile.h"

Projectile::Projectile(float initialPosX, float initialPosY, float targetPosX, float targetPosY, vector <GLuint> textures){
    setupShader();
    setTexture(textures[0]);

    setupSprite(
        vec3((initialPosX - 10), (initialPosY - 20), 1.0), //position
        vec3(1666/8, 1070/8, 1.0f),    //dimension
        1, 1                           //frames and animation
    );

    this->defaultSpeed = 10.0f;
    this->targetPosX = targetPosX;
    //Mouse Y is backwards
    this->targetPosY = HEIGHT - targetPosY;
    this->initialPosX = initialPosX - 10.0;
    this->initialPosY = initialPosY - 20.0;

    calculateDirections();

    this->isFacingRight = true;
    this->isOutOfRange = false;
    this->FPS = 30.0;
    this->textures = textures;
}

void Projectile::setTexture(GLuint texture) {
    this->texture = texture;
}

void Projectile::calculateDirections() {
    this->directionX = this->targetPosX - this->initialPosX;
    this->directionY = this->targetPosY - this->initialPosY;

    // Normalizar o vetor
    float length = sqrt(directionX * directionX + directionY * directionY);
    if (length != 0) {
        directionX /= length;
        directionY /= length;
    }

    // Calcular o ângulo em radianos usando atan2
    this->angle = atan2(this->directionY, this->directionX);
    //this->angle = angleRadians * 180.0f / M_PI;

    // Definir a velocidade com base no vetor direção e na velocidade desejada
    xSpeed = directionX * defaultSpeed;
    ySpeed = (directionY * defaultSpeed);
}

void Projectile::move() {
    this->position.x += xSpeed;
    this->position.y += ySpeed;

    if(this->position.x >= 960.0 || this->position.x <= 0.0 ||
       this->position.y >= 540.0 || this->position.y <= groundLevel - 65.0 )
        this->isOutOfRange = true;
}

void Projectile::drawSprite() {
    updateTexture();
    Sprite::drawSprite();
};

void Projectile::updateTexture() {
	float currentTime = glfwGetTime();
	float deltaTime = currentTime - this->lastTime;

	if (deltaTime >= 1.0 / this->FPS) {
        frameID += 1;
        if(frameID == 31)
            frameID = 5;
        setTexture(textures[frameID]);
		this->lastTime = currentTime;
	}	
};