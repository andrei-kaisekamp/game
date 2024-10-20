#include "GameEngine.h"
#include <Sprite.h>
#include <Background.h>
#include <Magician.h>
#include <GameEngine.h>
#include <BackgroundManager.h>
#include <Projectile.h>

bool GameEngine::mouseClicked = false;
double GameEngine::mouseClickX = 0.0;
double GameEngine::mouseClickY = 0.0;
  

void GameEngine::initialize() {
    initializeGL();
	loadProjectileTextures();
}

void GameEngine::run() {
	BackgroundManager *background = new BackgroundManager();
	Magician *magician = new Magician("textures/characters/magican/Idle.png");
	Projectile *projectile = nullptr;
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

		if(this->mouseClicked){
			if(projectile == nullptr)
				projectile = new Projectile(magician->getPosX(), (magician->getPosY()), mouseClickX, mouseClickY, this->projectileTextureContainer);
		}

		background->drawSprite();
		magician->drawSprite();

		if(projectile != nullptr){
			projectile->move();
			projectile->drawSprite();
			if(projectile->isOutOfRange)
				projectile = nullptr;
		}

		glfwSwapBuffers(window);
	}
}

void GameEngine::loadProjectileTextures() {
    GLuint texture;
    int imgWidth, imgHeight;
    for(int i = 0; i < 31; i++) {
        texture = loadTexture(("textures/projectile/" + to_string(i) + ".png"), imgWidth, imgHeight);
        projectileTextureContainer.push_back(texture);
    };
}

GLuint GameEngine::loadTexture(string filePath, int &imgWidth, int &imgHeight) {
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
}

void GameEngine::initializeGL() {
	glfwInit();

    window = glfwCreateWindow(WIDTH, HEIGHT, "JOGO FODA AG", nullptr, nullptr);
	glfwMakeContextCurrent(window);

	glfwSetKeyCallback(window, key_callback);
	
	glfwSetMouseButtonCallback(window, mouse_button_callback);

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
}

void GameEngine::mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
    if (button == GLFW_MOUSE_BUTTON_LEFT) {
        if (action ==GLFW_PRESS ){
			mouseClicked = true;
        	glfwGetCursorPos(window, &mouseClickX, &mouseClickY);
		}
		if(action ==GLFW_RELEASE)
			mouseClicked = false;
    }
};