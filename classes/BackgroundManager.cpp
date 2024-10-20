#include "BackgroundManager.h"

BackgroundManager::BackgroundManager() {
    Background *layer;
    layer = new Background("textures/background/layers/1.png", 1);
    skyLayers.push_back(layer);
    allLayers.push_back(layer);

	layer = new Background("textures/background/layers/clouds.png", 2);
    skyLayers.push_back(layer);
    allLayers.push_back(layer);

	layer = new Background("textures/background/layers/2.png", 3);
    skyLayers.push_back(layer);
    allLayers.push_back(layer);

	layer = new Background("textures/background/layers/3.png", 4);
    allLayers.push_back(layer);

	layer = new Background("textures/background/layers/4.png", 5);
    allLayers.push_back(layer);

	layer = new Background("textures/background/layers/5.png", 6);
    allLayers.push_back(layer);

    layer = new Background("textures/background/layers/7.png", 7);
    allLayers.push_back(layer);
}

void BackgroundManager::moveBackgroundLeft() {
    for (int i = 0; i < allLayers.size(); i++) {
			allLayers[i]->moveLeft();
		}
}

void BackgroundManager::moveBackgroundRight() {
    for (int i = 0; i < allLayers.size(); i++) {
		allLayers[i]->moveRight();
	}
}

void BackgroundManager::moveSky() {
    for (int i = 0; i < skyLayers.size(); i++) {
		skyLayers[i]->moveSky();
	}
}

void BackgroundManager::drawSprite() {
    for (int i = 0; i < allLayers.size(); i++) {
		allLayers[i]->drawSprite();
	}
};