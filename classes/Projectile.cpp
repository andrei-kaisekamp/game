#include "Projectile.h"

Projectile::Projectile(float targetPosX, float targetPosY, vector <GLuint> textures, Magician *magician){
    this->magician = magician;
    this->defaultSpeed = 10.0f;
    this->targetPosX = targetPosX;
    this->targetPosY = HEIGHT - targetPosY;      //Mouse Y is backwards
    this->initialPosX = this->magician->getPosX() - 10.0;
    this->initialPosY = this->magician->getPosY() - 20.0;

    this->isFacingRight = true; //Not used because we use angle
    this->isOutOfRange = false;
    this->FPS = 30.0;
    this->textures = textures;

    setupShader();
    setTexture(textures[0]);

    setupSprite(
        vec3((this->initialPosX - 10), (this->initialPosY - 20), 1.0), //position
        vec3(1666/8, 1070/8, 1.0f),    //dimension
        1, 1                           //frames and animation
    );

    calculateDirections();
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
    xSpeed = directionX * defaultSpeed*2;
    ySpeed = (directionY * defaultSpeed*2);
}

void Projectile::move() {

    float lastPositionX = this->position.x;
    float lastPositionY = this->position.y;

    this->position.x += xSpeed;
    this->position.y += ySpeed;

    ySpeed -= defaultGravity / 2;

    float difPositionX = this->position.x - lastPositionX;
    float difPositionY = this->position.y - lastPositionY;
    
    this->angle = atan2(difPositionY, difPositionX);

    if(characterIsMoving){
        if(magician->isFacingRight)
            position.x -= 1 + (static_cast<float>(7)/2);
        else
            position.x += 1 + (static_cast<float>(7)/2);
    }

    if(this->position.x >= 960.0 || this->position.x <= 0.0 ||
       this->position.y <= groundLevel - 65.0 )
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