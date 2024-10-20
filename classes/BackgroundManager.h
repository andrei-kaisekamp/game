#include "Background.h"
#include <vector>

#ifndef BACKGROUNDMANAGER_H
#define BACKGROUNDMANAGER_H

class BackgroundManager{
public:
    BackgroundManager();
    void moveBackgroundLeft();
    void moveBackgroundRight();
    void moveSky();
    void drawSprite();
private:
    vector <Background*> skyLayers;
    vector <Background*> allLayers;
};

#endif