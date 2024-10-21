#include "TextureLoader.h"

TextureLoader::TextureLoader() {}

void TextureLoader::loadTextures() {
    loadBackgroundTextures();
    loadExplosionTextures();
    loadMagicianTextures();
    loadProjectileTextures();
}

void TextureLoader::loadBackgroundTextures() {
    GLuint texture;
    int width, height;

    for(int i = 1; i <= 8; i++) {
        texture = loadTexture(("textures/background/layers/" + to_string(i) + ".png"), width, height);
        backgroundTextures.textures.push_back(texture);
    };

    backgroundTextures.height = height;
    backgroundTextures.width = width;
}

void TextureLoader::loadProjectileTextures() {
    GLuint texture;
    int width, height;

    for(int i = 0; i <= 30; i++) {
        texture = loadTexture(("textures/projectile/" + to_string(i) + ".png"), width, height);
        projectileTextures.textures.push_back(texture);
    };

    projectileTextures.height = height;
    projectileTextures.width = width;
}

void TextureLoader::loadExplosionTextures() {
    GLuint texture;
    int width, height;

    for(int i = 1; i <= 10; i++) {
        texture = loadTexture(("textures/effects/explosion/" + to_string(i) + ".png"), width, height);
        explosionTextures.textures.push_back(texture);
    };

    explosionTextures.height = height;
    explosionTextures.width = width;
}

void TextureLoader::loadMagicianTextures() {
    GLuint texture;
    int width, height;

    texture = loadTexture(("textures/characters/magican/Idle.png"), width, height);
    magicianTextures.textures.push_back(texture);

    texture = loadTexture(("textures/characters/magican/Run.png"), width, height);
    magicianTextures.textures.push_back(texture);
    
    texture = loadTexture(("textures/characters/magican/Jump.png"), width, height);
    magicianTextures.textures.push_back(texture);

    magicianTextures.height = height;
    magicianTextures.width = width;
}

GLuint TextureLoader::loadTexture(string filePath, int &imgWidth, int &imgHeight) {
	GLuint texture;

	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	int nrChannels;
	unsigned char *data = stbi_load(filePath.c_str(), &imgWidth, &imgHeight, &nrChannels, 0);

	if (data){
		if (nrChannels == 3) // jpg, bmp
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, imgWidth, imgHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		else // png
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imgWidth, imgHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
		std::cout << "Failed to load texture" << filePath << std::endl;

	return texture;
};