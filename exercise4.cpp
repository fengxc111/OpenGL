#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <random>
#include <ctime>
#include "shader.h"

using namespace std;

//窗口回调函数
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(600, 600, u8"随机雪花", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	Shader ourShader("shaders/exercise4.vs", "shaders/exercise4.fs");

	float vertices[] = {
		0.1f, 0.05f, 0.0f,
		0.45f, 0.05f, 0.0f,
		0.6f, 0.2f, 0.0f,
		0.65f, 0.2f, 0.0f,
		0.5f, 0.05f, 0.0f,
		0.65f, 0.05f, 0.0f,
		0.75f, 0.15f, 0.0f,
		0.8f, 0.15f, 0.0f,
		0.7f, 0.05f, 0.0f,
		0.8f, 0.05f, 0.0f,
		0.85f, 0.0f, 0.0f,

		0.8f, -0.05f, 0.0f,
		0.7f, -0.05f, 0.0f,
		0.8f, -0.15f, 0.0f,
		0.75f, -0.15f, 0.0f,
		0.65f, -0.05f, 0.0f,
		0.5f, -0.05f, 0.0f,
		0.65f, -0.2f, 0.0f,
		0.6f, -0.2f, 0.0f,
		0.45f, -0.05f, 0.0f,
		0.10f, -0.05f, 0.0f,

		0.35f, -0.30f, 0.0f,
		0.56f, -0.30f, 0.0f,
		0.59f, -0.33f, 0.0f,
		0.38f, -0.33f, 0.0f,
		0.49f, -0.44f, 0.0f,
		0.63f, -0.44f, 0.0f,
		0.66f, -0.47f, 0.0f,
		0.52f, -0.47f, 0.0f,
		0.58f, -0.53f, 0.0f,
		0.60f, -0.60f, 0.0f,

		0.53f, -0.58f, 0.0f,
		0.47f, -0.52f, 0.0f,
		0.47f, -0.66f, 0.0f,
		0.44f, -0.63f, 0.0f,
		0.44f, -0.49f, 0.0f,
		0.33f, -0.38f, 0.0f,
		0.33f, -0.59f, 0.0f,
		0.30f, -0.56f, 0.0f,
		0.30f, -0.35f, 0.0f,
		0.05f, -0.10f, 0.0f,

		0.05f, -0.45f, 0.0f,
		0.20f, -0.60f, 0.0f,
		0.20f, -0.65f, 0.0f,
		0.05f, -0.50f, 0.0f,
		0.05f, -0.65f, 0.0f,
		0.15f, -0.75f, 0.0f,
		0.15f, -0.80f, 0.0f,
		0.05f, -0.70f, 0.0f,
		0.05f, -0.80f, 0.0f,
		0.00f, -0.85f, 0.0f,

		-0.05f, -0.80f, 0.0f,
		-0.05f, -0.70f, 0.0f,
		-0.15f, -0.80f, 0.0f,
		-0.15f, -0.75f, 0.0f,
		-0.05f, -0.65f, 0.0f,
		-0.05f, -0.50f, 0.0f,
		-0.20f, -0.65f, 0.0f,
		-0.20f, -0.60f, 0.0f,
		-0.05f, -0.45f, 0.0f,
		-0.05f, -0.10f, 0.0f,

		-0.30f, -0.35f, 0.0f,
		-0.30f, -0.56f, 0.0f,
		-0.33f, -0.59f, 0.0f,
		-0.33f, -0.38f, 0.0f,
		-0.44f, -0.49f, 0.0f,
		-0.44f, -0.63f, 0.0f,
		-0.47f, -0.66f, 0.0f,
		-0.47f, -0.52f, 0.0f,
		-0.53f, -0.58f, 0.0f,
		-0.60f, -0.60f, 0.0f,

		-0.58f, -0.53f, 0.0f,
		-0.52f, -0.47f, 0.0f,
		-0.66f, -0.47f, 0.0f,
		-0.63f, -0.44f, 0.0f,
		-0.49f, -0.44f, 0.0f,
		-0.38f, -0.33f, 0.0f,
		-0.59f, -0.33f, 0.0f,
		-0.56f, -0.30f, 0.0f,
		-0.35f, -0.30f, 0.0f,
		-0.10f, -0.05f, 0.0f,

		-0.45f, -0.05f, 0.0f,
		-0.60f, -0.20f, 0.0f,
		-0.65f, -0.20f, 0.0f,
		-0.50f, -0.05f, 0.0f,
		-0.65f, -0.05f, 0.0f,
		-0.75f, -0.15f, 0.0f,
		-0.80f, -0.15f, 0.0f,
		-0.70f, -0.05f, 0.0f,
		-0.80f, -0.05f, 0.0f,
		-0.85f, 0.00f, 0.0f,

		-0.80f, 0.05f, 0.0f,
		-0.70f, 0.05f, 0.0f,
		-0.80f, 0.15f, 0.0f,
		-0.75f, 0.15f, 0.0f,
		-0.65f, 0.05f, 0.0f,
		-0.50f, 0.05f, 0.0f,
		-0.65f, 0.20f, 0.0f,
		-0.60f, 0.20f, 0.0f,
		-0.45f, 0.05f, 0.0f,
		-0.10f, 0.05f, 0.0f,

		-0.35f, 0.30f, 0.0f,
		-0.56f, 0.30f, 0.0f,
		-0.59f, 0.33f, 0.0f,
		-0.38f, 0.33f, 0.0f,
		-0.49f, 0.44f, 0.0f,
		-0.63f, 0.44f, 0.0f,
		-0.66f, 0.47f, 0.0f,
		-0.52f, 0.47f, 0.0f,
		-0.58f, 0.53f, 0.0f,
		-0.60f, 0.60f, 0.0f,

		-0.53f, 0.58f, 0.0f,
		-0.47f, 0.52f, 0.0f,
		-0.47f, 0.66f, 0.0f,
		-0.44f, 0.63f, 0.0f,
		-0.44f, 0.49f, 0.0f,
		-0.33f, 0.38f, 0.0f,
		-0.33f, 0.59f, 0.0f,
		-0.30f, 0.56f, 0.0f,
		-0.30f, 0.35f, 0.0f,
		-0.05f, 0.10f, 0.0f,

		-0.05f, 0.45f, 0.0f,
		-0.20f, 0.60f, 0.0f,
		-0.20f, 0.65f, 0.0f,
		-0.05f, 0.50f, 0.0f,
		-0.05f, 0.65f, 0.0f,
		-0.15f, 0.75f, 0.0f,
		-0.15f, 0.80f, 0.0f,
		-0.05f, 0.70f, 0.0f,
		-0.05f, 0.80f, 0.0f,
		0.00f, 0.85f, 0.0f,

		0.05f, 0.80f, 0.0f,
		0.05f, 0.70f, 0.0f,
		0.15f, 0.80f, 0.0f,
		0.15f, 0.75f, 0.0f,
		0.05f, 0.65f, 0.0f,
		0.05f, 0.50f, 0.0f,
		0.20f, 0.65f, 0.0f,
		0.20f, 0.60f, 0.0f,
		0.05f, 0.45f, 0.0f,
		0.05f, 0.10f, 0.0f,


		0.30f, 0.35f, 0.0f,
		0.30f, 0.56f, 0.0f,
		0.33f, 0.59f, 0.0f,
		0.33f, 0.38f, 0.0f,
		0.44f, 0.49f, 0.0f,
		0.44f, 0.63f, 0.0f,
		0.47f, 0.66f, 0.0f,
		0.47f, 0.52f, 0.0f,
		0.53f, 0.58f, 0.0f,
		0.60f, 0.60f, 0.0f,

		0.58f, 0.53f, 0.0f,
		0.52f, 0.47f, 0.0f,
		0.66f, 0.47f, 0.0f,
		0.63f, 0.44f, 0.0f,
		0.49f, 0.44f, 0.0f,
		0.38f, 0.33f, 0.0f,
		0.59f, 0.33f, 0.0f,
		0.56f, 0.30f, 0.0f,
		0.35f, 0.30f, 0.0f,
		0.10f, 0.05f, 0.0f
	};

	glm::vec3 Positions[] = {
glm::vec3(0.0f,  0.0f,  0.0f),
glm::vec3(2.0f,  5.0f, -15.0f),
glm::vec3(-1.5f, -2.2f, -2.5f),
glm::vec3(-3.8f, -2.0f, -12.3f),
glm::vec3(2.4f, -0.4f, -3.5f),
	};

	unsigned int VAO, VBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);


	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);


	int i = 0;
	glm::mat4 transform = glm::mat4(1.0f);
	float x, y, prex, prey;
	x = 0;
	y = 0.8;
	prex = 0;
	prey = 0;
	while (!glfwWindowShouldClose(window))
	{
		processInput(window);
		glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		i++;

		transform = glm::mat4(1.0f);
		if (y <= -1.4)
		{
			//x = sin(rand() % 1000) * 0.8;
			uniform_real_distribution<double> u(-1, 1);
			default_random_engine e(time(NULL));
			x = u(e);
			y = 0.9;
		}
		else
		{
			y = y - 0.005;
		}

		transform = glm::translate(transform, glm::vec3(x, y, 0.0f));

		ourShader.use();
		transform = glm::scale(transform, glm::vec3(0.25, 0.25, 1));
		transform = glm::rotate(transform, (float)glfwGetTime() * glm::radians(50.0f), glm::vec3(0.0f, 0.0f, 1.0f));
		unsigned int transformLoc = glGetUniformLocation(ourShader.ID, "transform");
		glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));

		glBindVertexArray(VAO);
		glDrawArrays(GL_LINE_STRIP, 0, 161);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);

	glfwTerminate();
	return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, 600, 600);

}

void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}