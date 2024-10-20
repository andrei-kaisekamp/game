#include "GameEngine.h"
#include <Sprite.h>
#include <Background.h>
#include <Magician.h>
#include <GameEngine.h>
#include <BackgroundManager.h>

void GameEngine::initialize() {
    initializeGL();
}

void GameEngine::run() {
	BackgroundManager *background = new BackgroundManager();
	Magician *magician = new Magician("textures/characters/magican/Idle.png");

	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glfwPollEvents();

		if(!magician->isJumping)
			magician->idle();

		background->moveSky();

		if (keys[GLFW_KEY_LEFT] || keys[GLFW_KEY_A]) {
			background->moveBackgroundLeft();
			magician->moveLeft();
		}

		if (keys[GLFW_KEY_RIGHT] || keys[GLFW_KEY_D]) {
			background->moveBackgroundRight();
			magician->moveRight();
		}

		if (keys[GLFW_KEY_UP] || keys[GLFW_KEY_W]) {
            magician->isJumping = true;
		}

		if(magician->isJumping){
			magician->jump();
		}

		background->drawSprite();
		magician->drawSprite();

		glfwSwapBuffers(window);
	}
}

void GameEngine::initializeGL() {
	glfwInit();

    window = glfwCreateWindow(WIDTH, HEIGHT, "JOGO FODA AG", nullptr, nullptr);
	glfwMakeContextCurrent(window);

	glfwSetKeyCallback(window, key_callback);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		std::cout << "Failed to initialize GLAD" << std::endl;

	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	glViewport(0, 0, width, height);

	glActiveTexture(GL_TEXTURE0);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_ALWAYS);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void GameEngine::key_callback(GLFWwindow *window, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);

	if (action == GLFW_PRESS)
	{
		keys[key] = true;
	}
	if (action == GLFW_RELEASE)
	{
		keys[key] = false;
	}
};