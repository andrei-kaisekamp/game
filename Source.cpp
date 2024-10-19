#include <Globals.h>
#include <Sprite.h>
#include <Background.h>
#include <Magician.h>

// Protótipo da função de callback de teclado
void key_callback(GLFWwindow *window, int key, int scancode, int action, int mode);

bool keys[1024] = {false};

// Função MAIN
int main()
{
	// Inicialização da GLFW
	glfwInit();

	// Criação da janela GLFW
	GLFWwindow *window = glfwCreateWindow(WIDTH, HEIGHT, "Hello Sprites!", nullptr, nullptr);
	glfwMakeContextCurrent(window);

	// Fazendo o registro da função de callback para a janela GLFW
	glfwSetKeyCallback(window, key_callback);

	// GLAD: carrega todos os ponteiros d funções da OpenGL
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		std::cout << "Failed to initialize GLAD" << std::endl;

	// Definindo as dimensões da viewport com as mesmas dimensões da janela da aplicação
	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	glViewport(0, 0, width, height);

	// Sprite do fundo da cena
	Background *background = new Background("textures/background/game_background.png");
	Magician *magician = new Magician("textures/characters/magican/Idle.png");
		
	// Ativando o primeiro buffer de textura da OpenGL
	glActiveTexture(GL_TEXTURE0);

	// Habilitar a transparência
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// Habilitar o teste de profundidade
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_ALWAYS);

	// Loop da aplicação - "game loop"
	while (!glfwWindowShouldClose(window))
	{
		// Checa se houveram eventos de input (key pressed, mouse moved etc.) e chama as funções de callback correspondentes
		glfwPollEvents();

		// Limpa o buffer de cor
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // cor de fundo
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//vec2 offsetTex = vec2(0.0, 0.0);
		//glUniform2f(glGetUniformLocation(background->shader, "offsetTex"), offsetTex.s, offsetTex.t);
		background->drawSprite();
		if (keys[GLFW_KEY_LEFT] || keys[GLFW_KEY_A])
			magician->moveLeft();
		if (keys[GLFW_KEY_RIGHT] || keys[GLFW_KEY_D])
			magician->moveRight();
		// Incremento circular (em loop) do índice do frame
		/*
		float now = glfwGetTime();
		float dt = now - magician->lastTime;
		if (dt >= 1.0 / magician->FPS)
		{
			magician->iFrame = (magician->iFrame + 1) % magician->nFrames; // incrementando ciclicamente o indice do Frame
			magician->lastTime = now;
		}	
		offsetTex.s = magician->iFrame * magician->d.s;
		offsetTex.t = 0.0;
		*/

		//glUseProgram(magician->shader);
		//glUniform2f(glGetUniformLocation(magician->shader, "offsetTex"), offsetTex.s, offsetTex.t);
		magician->drawSprite();
		// Troca os buffers da tela
		glfwSwapBuffers(window);
	}
	glfwTerminate();
	return 0;
}

void key_callback(GLFWwindow *window, int key, int scancode, int action, int mode)
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
