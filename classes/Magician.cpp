#include "Magician.h"

Magician::Magician(string filePath){
    int imgWidth, imgHeight;
    setupShader();
    loadTexture(filePath, imgWidth, imgHeight);
    setupSprite(
        vec3((static_cast<float>(WIDTH)/2), groundLevel, 0.0), 
        vec3(imgWidth*1.5 / 8.0, imgHeight*1.5, 1.0), 8, 1
    );
    this->isFacingRight = true;
    this->isJumping = false;
    this->firstJumpLoop = true;
    this->jumpSpeed = 15.0;
}

void Magician::moveLeft(){
    this->isFacingRight = false;
    this->moving();
}

void Magician::moveRight(){
    this->isFacingRight = true;
    this->moving();
}

void Magician::updateFrame(){
	float currentTime = glfwGetTime();
	float deltaTime = currentTime - this->lastTime;
	if (deltaTime >= 1.0 / this->FPS)
	{
		this->frameID = (this->frameID + 1) % this->frames;
		this->lastTime = currentTime;
	}	
	this->textureOffset.s = (static_cast<float>(this->frameID)) / frames;

    glUseProgram(this->shader);
	glUniform2f(glGetUniformLocation(this->shader, "offsetTex"), textureOffset.s, textureOffset.t);
}

void Magician::drawSprite(){
    updateFrame();
    Sprite::drawSprite();
}

void Magician::idle() {
    int imgWidth, imgHeight;
    loadTexture("textures/characters/magican/Idle.png", imgWidth, imgHeight);
}

void Magician::moving() {
    int imgWidth, imgHeight;
    loadTexture("textures/characters/magican/Run.png", imgWidth, imgHeight);
}

void Magician::jump() {
    int imgWidth, imgHeight;
    loadTexture("textures/characters/magican/Jump.png", imgWidth, imgHeight);

    this->position.y += jumpSpeed; 
    jumpSpeed -= defaultGravity;

    if(this->firstJumpLoop){
        this->firstJumpLoop = false;
        this->frameID = 0;
        this->lastTime = glfwGetTime();
    }

    // Quando o personagem atinge o chão novamente
    if (this->position.y <= groundLevel) {
        this->position.y = groundLevel;
        this->isJumping = false;
        this->firstJumpLoop = true;
        jumpSpeed = 15.0f;
		glUseProgram(this->shader);
		this->idle();
    }
}
;