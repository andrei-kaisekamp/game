#include "Magician.h"

Magician::Magician(string filePath){
    //: Sprite(filePath){

    int imgWidth, imgHeight;
    setupShader();
    loadTexture(filePath, imgWidth, imgHeight);
    setupSprite(
        vec3(50.0, 153.0, 0.0), 
        vec3(imgWidth*1.5 / 8.0, imgHeight*1.5, 1.0), 8, 1
    );
}

void Magician::moveLeft(){
    this->position.x -= speed;
}

void Magician::moveRight(){
    this->position.x += speed;
}

void Magician::updateFrame(){
	float currentTime = glfwGetTime();
	float deltaTime = currentTime - this->lastTime;
	if (deltaTime >= 1.0 / this->FPS)
	{
		this->frameID = (this->frameID + 1) % this->frames; // incrementando ciclicamente o indice do Frame
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
;