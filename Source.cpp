#include <Globals.h>
#include <Sprite.h>
#include <Background.h>
#include <Magician.h>
#include <BackgroundManager.h>
#include <TextureLoader.h>
#include <GameEngine.h>


int main() {
	GameEngine *engine = new GameEngine;
    engine->initialize();
	engine->run();
	glfwTerminate();
	return 0;
}