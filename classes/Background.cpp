#include "Background.h"

Background::Background(string filePath){
    //: Sprite(filePath){
    int imgWidth, imgHeight;
    setupShader();
    loadTexture(filePath, imgWidth, imgHeight);
    setupSprite(vec3((static_cast<float>(WIDTH) / 2), 
                     (static_cast<float>(HEIGHT) / 2), 1.0), 
                     vec3(static_cast<float>(imgWidth)*WIDTH/imgWidth, 
                     static_cast<float>(imgHeight)*HEIGHT/imgHeight, 1.0f), 1, 1);
};