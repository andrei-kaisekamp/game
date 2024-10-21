#include "Globals.h"
#include <vector>

#ifndef TEXTURELOADER_H
#define TEXTURELOADER_H

class TextureLoader {
public:
    TextureLoader();
    void loadTextures();

    Texture magicianTextures;
    Texture backgroundTextures;
    Texture projectileTextures;
    Texture explosionTextures;
private:
    GLuint loadTexture(string filePath, int &imgWidth, int &imgHeight);
    void loadMagicianTextures();
    void loadBackgroundTextures();
    void loadProjectileTextures();
    void loadExplosionTextures();
};


#endif