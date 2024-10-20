#ifndef GAME_ENGINE_H
#define GAME_ENGINE_H

#include "Globals.h"

class GameEngine{
public:
    void initialize();
    void run();
    static void key_callback(GLFWwindow *window, int key, int scancode, int action, int mode);
private:
  GLFWwindow *window;
  void initializeGL();
};
#endif