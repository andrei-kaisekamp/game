#include "BackgroundManager.h"

BackgroundManager::BackgroundManager(Texture textures) {
    Background *layer;
    layer = new Background(textures.textures[0], textures.width, textures.height, 1);
    skyLayers.push_back(layer);
    allLayers.push_back(layer);

	layer = new Background(textures.textures[1], textures.width, textures.height, 2);
    skyLayers.push_back(layer);
    allLayers.push_back(layer);

	layer = new Background(textures.textures[2], textures.width, textures.height, 3);
    skyLayers.push_back(layer);
    allLayers.push_back(layer);

	layer = new Background(textures.textures[3], textures.width, textures.height, 4);
    allLayers.push_back(layer);

	layer = new Background(textures.textures[4], textures.width, textures.height, 5);
    allLayers.push_back(layer);

	layer = new Background(textures.textures[5], textures.width, textures.height, 6);
    allLayers.push_back(layer);

    layer = new Background(textures.textures[6], textures.width, textures.height, 7);
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