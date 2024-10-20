#ifndef GAME_ENGINE_H
#define GAME_ENGINE_H

#include "Globals.h"
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
  static double mouseClickX;
  static double mouseClickY;
  static bool mouseClicked;

  vector <GLuint> projectileTextureContainer;
  void loadProjectileTextures();
  GLuint loadTexture(string filePath, int &imgWidth, int &imgHeight);
};
#endif