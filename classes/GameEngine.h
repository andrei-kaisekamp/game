#ifndef GAME_ENGINE_H
#define GAME_ENGINE_H

#include "Globals.h"
#include "TextureLoader.h"
#include <vector>

class GameEngine{
public:
    void initialize();
    void run();
    static void key_callback(GLFWwindow *window, int key, int scancode, int action, int mode);
    static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
    //vector projectiles
private:
    GLFWwindow *window;
    void initializeGL();
    void createWindow();
    void setCallback();
    void loadGLAD();
    void createViewPort();
    void configureOpenGLBuffers();
    void loadTextures();
    //void loadProjectileTextures();
    //void loadExplosionTextures();

    static double mouseClickX;
    static double mouseClickY;
    static bool mouseClicked;

    TextureLoader *textureLoader;

    //vector <GLuint> projectileTextureContainer;
    //vector <GLuint> explosionTextureContainer;
    
    GLuint loadTexture(string filePath, int &imgWidth, int &imgHeight);

};
#endif