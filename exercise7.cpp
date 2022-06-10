#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <random>
#include <ctime>
#include "shader_m.h"
using namespace std;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);//回调函数
void processInput(GLFWwindow* window);
//void mouse_callback(GLFWwindow* window, double xpos, double ypos);
//void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

const unsigned int SCR_HEIGHT = 600;
const unsigned int SCR_WIDTH = 600;

glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
float fov = 45.0f;

float deltaTime = 0.0f; // 当前帧与上一帧的时间差
float lastFrame = 0.0f; // 上一帧的时间

int main()
{
	glfwInit();//初始化glfw
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);//配置glfw，主版本号(Major)和次版本号(Minor)
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, u8"颜色填充", NULL, NULL);
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);


	gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);//初始化GLAD

	Shader ourShader("shaders/exercise7.vs", "shaders/exercise7.fs");

	float vertices1[] = {
		-0.80f, 0.025f, 0.0f, 0.45f, 0.5f, 1.0f,
		-0.80f, -0.025f, 0.0f,0.45f, 0.5f, 1.0f,
		0.8f, 0.025f, 0.0f,   0.45f, 0.5f, 1.0f,
		-0.80f, -0.025f, 0.0f, 0.45f, 0.5f, 1.0f,
		0.8f, 0.025f, 0.0f,   0.45f, 0.5f, 1.0f,
		0.8f, -0.025f, 0.0f,   0.45f, 0.5f, 1.0f,

		0.025f, 0.80f, 0.0f,  0.45f, 0.5f, 1.0f,
		-0.025f, 0.80f, 0.0f,  0.45f, 0.5f, 1.0f,
		0.025f, -0.80f, 0.0f,  0.45f, 0.5f, 1.0f,
		-0.025f, 0.80f, 0.0f,  0.45f, 0.5f, 1.0f,
		0.025f, -0.80f, 0.0f,  0.45f, 0.5f, 1.0f,
		-0.025f, -0.80f, 0.0f,  0.45f, 0.5f, 1.0f,

		0.58f, 0.53f, 0.0f, 0.45f, 0.5f, 1.0f,
		0.53f, 0.58f, 0.0f, 0.45f, 0.5f, 1.0f,
		-0.53f, -0.58f, 0.0f, 0.45f, 0.5f, 1.0f,
		-0.53f, -0.58f, 0.0f, 0.45f, 0.5f, 1.0f,
		-0.58f, -0.53f, 0.0f,0.45f, 0.5f, 1.0f,
		0.53f, 0.58f, 0.0f, 0.45f, 0.5f, 1.0f,

		-0.58f, 0.53f, 0.0f, 0.45f, 0.5f, 1.0f,
		-0.53f, 0.58f, 0.0f, 0.45f, 0.5f, 1.0f,
		0.53f, -0.58f, 0.0f, 0.45f, 0.5f, 1.0f,
		0.53f, -0.58f, 0.0f, 0.45f, 0.5f, 1.0f,
		0.58f, -0.53f, 0.0f, 0.45f, 0.5f, 1.0f,
		-0.53f, 0.58f, 0.0f, 0.45f, 0.5f, 1.0f,

		0.45f, 0.025f, 0.0f,  0.45f, 0.5f, 1.0f,
		0.65f, 0.2f, 0.0f,   1.0f, 1.0f, 1.0f,
		0.6f, 0.2f, 0.0f,    1.0f, 1.0f, 1.0f,
		0.45f, 0.025f, 0.0f,  0.45f, 0.5f, 1.0f,
		0.65f, 0.2f, 0.0f,   1.0f, 1.0f, 1.0f,
		0.5f, 0.025f, 0.0f,   0.45f, 0.5f, 1.0f,

		0.65f, 0.025f, 0.0f,  0.45f, 0.5f, 1.0f,
		0.8f, 0.15f, 0.0f,   1.0f, 1.0f, 1.0f,
		0.75f, 0.15f, 0.0f,  1.0f, 1.0f, 1.0f,
		0.65f, 0.025f, 0.0f,  0.45f, 0.5f, 1.0f,
		0.8f, 0.15f, 0.0f,   1.0f, 1.0f, 1.0f,
		0.7f, 0.025f, 0.0f,   0.45f, 0.5f, 1.0f,

		0.45f, -0.025f, 0.0f,  0.45f, 0.5f, 1.0f,
		0.65f, -0.2f, 0.0f,   1.0f, 1.0f, 1.0f,
		0.6f, -0.2f, 0.0f,    1.0f, 1.0f, 1.0f,
		0.45f, -0.025f, 0.0f,  0.45f, 0.5f, 1.0f,
		0.65f, -0.2f, 0.0f,   1.0f, 1.0f, 1.0f,
		0.5f, -0.025f, 0.0f,   0.45f, 0.5f, 1.0f,

		0.65f, -0.025f, 0.0f,  0.45f, 0.5f, 1.0f,
		0.8f, -0.15f, 0.0f,   1.0f, 1.0f, 1.0f,
		0.75f, -0.15f, 0.0f,  1.0f, 1.0f, 1.0f,
		0.65f, -0.025f, 0.0f,  0.45f, 0.5f, 1.0f,
		0.8f, -0.15f, 0.0f,   1.0f, 1.0f, 1.0f,
		0.7f, -0.025f, 0.0f,   0.45f, 0.5f, 1.0f,

		-0.45f, 0.025f, 0.0f,  0.45f, 0.5f, 1.0f,
		-0.65f, 0.2f, 0.0f,   1.0f, 1.0f, 1.0f,
		-0.6f, 0.2f, 0.0f,    1.0f, 1.0f, 1.0f,
		-0.45f, 0.025f, 0.0f,  0.45f, 0.5f, 1.0f,
		-0.65f, 0.2f, 0.0f,   1.0f, 1.0f, 1.0f,
		-0.5f, 0.025f, 0.0f,   0.45f, 0.5f, 1.0f,

		-0.65f, 0.025f, 0.0f,  0.45f, 0.5f, 1.0f,
		-0.8f, 0.15f, 0.0f,   1.0f, 1.0f, 1.0f,
		-0.75f, 0.15f, 0.0f,  1.0f, 1.0f, 1.0f,
		-0.65f, 0.025f, 0.0f,  0.45f, 0.5f, 1.0f,
		-0.8f, 0.15f, 0.0f,   1.0f, 1.0f, 1.0f,
		-0.7f, 0.025f, 0.0f,   0.45f, 0.5f, 1.0f,

		-0.45f, -0.025f, 0.0f,  0.45f, 0.5f, 1.0f,
		-0.65f, -0.2f, 0.0f,   1.0f, 1.0f, 1.0f,
		-0.6f, -0.2f, 0.0f,    1.0f, 1.0f, 1.0f,
		-0.45f, -0.025f, 0.0f,  0.45f, 0.5f, 1.0f,
		-0.65f, -0.2f, 0.0f,   1.0f, 1.0f, 1.0f,
		-0.5f, -0.025f, 0.0f,   0.45f, 0.5f, 1.0f,

		-0.65f, -0.025f, 0.0f,  0.45f, 0.5f, 1.0f,
		-0.8f, -0.15f, 0.0f,   1.0f, 1.0f, 1.0f,
		-0.75f, -0.15f, 0.0f,  1.0f, 1.0f, 1.0f,
		-0.65f, -0.025f, 0.0f,  0.45f, 0.5f, 1.0f,
		-0.8f, -0.15f, 0.0f,   1.0f, 1.0f, 1.0f,
		-0.7f, -0.025f, 0.0f,   0.45f, 0.5f, 1.0f,

		0.35f, -0.30f, 0.0f, 0.45f, 0.5f, 1.0f,
		0.59f, -0.33f, 0.0f, 1.0f, 1.0f, 1.0f,
		0.56f, -0.30f, 0.0f, 1.0f, 1.0f, 1.0f,
		0.35f, -0.30f, 0.0f, 0.45f, 0.5f, 1.0f,
		0.59f, -0.33f, 0.0f, 1.0f, 1.0f, 1.0f,
		0.38f, -0.33f, 0.0f, 0.45f, 0.5f, 1.0f,

		0.49f, -0.44f, 0.0f, 0.45f, 0.5f, 1.0f,
		0.66f, -0.47f, 0.0f, 1.0f, 1.0f, 1.0f,
		0.63f, -0.44f, 0.0f, 1.0f, 1.0f, 1.0f,
		0.49f, -0.44f, 0.0f, 0.45f, 0.5f, 1.0f,
		0.66f, -0.47f, 0.0f, 1.0f, 1.0f, 1.0f,
		0.52f, -0.47f, 0.0f, 0.45f, 0.5f, 1.0f,

		0.47f, -0.52f, 0.0f, 0.45f, 0.5f, 1.0f,
		0.44f, -0.63f, 0.0f, 1.0f, 1.0f, 1.0f,
		0.47f, -0.66f, 0.0f, 1.0f, 1.0f, 1.0f,
		0.47f, -0.52f, 0.0f, 0.45f, 0.5f, 1.0f,
		0.44f, -0.63f, 0.0f, 1.0f, 1.0f, 1.0f,
		0.44f, -0.49f, 0.0f, 0.45f, 0.5f, 1.0f,

			0.33f, -0.38f, 0.0f, 0.45f, 0.5f, 1.0f,
			0.30f, -0.56f, 0.0f, 1.0f, 1.0f, 1.0f,
			0.33f, -0.59f, 0.0f, 1.0f, 1.0f, 1.0f,
			0.33f, -0.38f, 0.0f, 0.45f, 0.5f, 1.0f,
			0.30f, -0.56f, 0.0f, 1.0f, 1.0f, 1.0f,
			0.30f, -0.35f, 0.0f, 0.45f, 0.5f, 1.0f,

			0.35f, 0.30f, 0.0f, 0.45f, 0.5f, 1.0f,
			0.59f, 0.33f, 0.0f, 1.0f, 1.0f, 1.0f,
			0.56f, 0.30f, 0.0f, 1.0f, 1.0f, 1.0f,
			0.35f, 0.30f, 0.0f, 0.45f, 0.5f, 1.0f,
			0.59f, 0.33f, 0.0f, 1.0f, 1.0f, 1.0f,
			0.38f, 0.33f, 0.0f, 0.45f, 0.5f, 1.0f,

			0.49f, 0.44f, 0.0f, 0.45f, 0.5f, 1.0f,
			0.66f, 0.47f, 0.0f, 1.0f, 1.0f, 1.0f,
			0.63f, 0.44f, 0.0f, 1.0f, 1.0f, 1.0f,
			0.49f, 0.44f, 0.0f, 0.45f, 0.5f, 1.0f,
			0.66f, 0.47f, 0.0f, 1.0f, 1.0f, 1.0f,
			0.52f, 0.47f, 0.0f, 0.45f, 0.5f, 1.0f,

			0.47f, 0.52f, 0.0f, 0.45f, 0.5f, 1.0f,
			0.44f, 0.63f, 0.0f, 1.0f, 1.0f, 1.0f,
			0.47f, 0.66f, 0.0f, 1.0f, 1.0f, 1.0f,
			0.47f, 0.52f, 0.0f, 0.45f, 0.5f, 1.0f,
			0.44f, 0.63f, 0.0f, 1.0f, 1.0f, 1.0f,
			0.44f, 0.49f, 0.0f, 0.45f, 0.5f, 1.0f,

			0.33f, 0.38f, 0.0f, 0.45f, 0.5f, 1.0f,
			0.30f, 0.56f, 0.0f, 1.0f, 1.0f, 1.0f,
			0.33f, 0.59f, 0.0f, 1.0f, 1.0f, 1.0f,
			0.33f, 0.38f, 0.0f, 0.45f, 0.5f, 1.0f,
			0.30f, 0.56f, 0.0f, 1.0f, 1.0f, 1.0f,
			0.30f, 0.35f, 0.0f, 0.45f, 0.5f, 1.0f,

			-0.35f, -0.30f, 0.0f, 0.45f, 0.5f, 1.0f,
			-0.59f, -0.33f, 0.0f, 1.0f, 1.0f, 1.0f,
			-0.56f, -0.30f, 0.0f, 1.0f, 1.0f, 1.0f,
			-0.35f, -0.30f, 0.0f, 0.45f, 0.5f, 1.0f,
			-0.59f, -0.33f, 0.0f, 1.0f, 1.0f, 1.0f,
			-0.38f, -0.33f, 0.0f, 0.45f, 0.5f, 1.0f,

			-0.49f, -0.44f, 0.0f, 0.45f, 0.5f, 1.0f,
			-0.66f, -0.47f, 0.0f, 1.0f, 1.0f, 1.0f,
			-0.63f, -0.44f, 0.0f, 1.0f, 1.0f, 1.0f,
			-0.49f, -0.44f, 0.0f, 0.45f, 0.5f, 1.0f,
			-0.66f, -0.47f, 0.0f, 1.0f, 1.0f, 1.0f,
			-0.52f, -0.47f, 0.0f, 0.45f, 0.5f, 1.0f,

			-0.47f, -0.52f, 0.0f, 0.45f, 0.5f, 1.0f,
			-0.44f, -0.63f, 0.0f, 1.0f, 1.0f, 1.0f,
			-0.47f, -0.66f, 0.0f, 1.0f, 1.0f, 1.0f,
			-0.47f, -0.52f, 0.0f, 0.45f, 0.5f, 1.0f,
			-0.44f, -0.63f, 0.0f, 1.0f, 1.0f, 1.0f,
			-0.44f, -0.49f, 0.0f, 0.45f, 0.5f, 1.0f,

			-0.33f, -0.38f, 0.0f, 0.45f, 0.5f, 1.0f,
			-0.30f, -0.56f, 0.0f, 1.0f, 1.0f, 1.0f,
			-0.33f, -0.59f, 0.0f, 1.0f, 1.0f, 1.0f,
			-0.33f, -0.38f, 0.0f, 0.45f, 0.5f, 1.0f,
			-0.30f, -0.56f, 0.0f, 1.0f, 1.0f, 1.0f,
			-0.30f, -0.35f, 0.0f, 0.45f, 0.5f, 1.0f,

			-0.35f, 0.30f, 0.0f, 0.45f, 0.5f, 1.0f,
			-0.59f, 0.33f, 0.0f, 1.0f, 1.0f, 1.0f,
			-0.56f, 0.30f, 0.0f, 1.0f, 1.0f, 1.0f,
			-0.35f, 0.30f, 0.0f, 0.45f, 0.5f, 1.0f,
			-0.59f, 0.33f, 0.0f, 1.0f, 1.0f, 1.0f,
			-0.38f, 0.33f, 0.0f, 0.45f, 0.5f, 1.0f,

			-0.49f, 0.44f, 0.0f, 0.45f, 0.5f, 1.0f,
			-0.66f, 0.47f, 0.0f, 1.0f, 1.0f, 1.0f,
			-0.63f, 0.44f, 0.0f, 1.0f, 1.0f, 1.0f,
			-0.49f, 0.44f, 0.0f, 0.45f, 0.5f, 1.0f,
			-0.66f, 0.47f, 0.0f, 1.0f, 1.0f, 1.0f,
			-0.52f, 0.47f, 0.0f, 0.45f, 0.5f, 1.0f,

			-0.47f, 0.52f, 0.0f, 0.45f, 0.5f, 1.0f,
			-0.44f, 0.63f, 0.0f, 1.0f, 1.0f, 1.0f,
			-0.47f, 0.66f, 0.0f, 1.0f, 1.0f, 1.0f,
			-0.47f, 0.52f, 0.0f, 0.45f, 0.5f, 1.0f,
			-0.44f, 0.63f, 0.0f, 1.0f, 1.0f, 1.0f,
			-0.44f, 0.49f, 0.0f, 0.45f, 0.5f, 1.0f,

			-0.33f, 0.38f, 0.0f, 0.45f, 0.5f, 1.0f,
			-0.30f, 0.56f, 0.0f, 1.0f, 1.0f, 1.0f,
			-0.33f, 0.59f, 0.0f, 1.0f, 1.0f, 1.0f,
			-0.33f, 0.38f, 0.0f, 0.45f, 0.5f, 1.0f,
			-0.30f, 0.56f, 0.0f, 1.0f, 1.0f, 1.0f,
			-0.30f, 0.35f, 0.0f, 0.45f, 0.5f, 1.0f,

			0.025f, -0.45f, 0.0f, 0.45f, 0.5f, 1.0f,
			0.20f, -0.65f, 0.0f, 1.0f, 1.0f, 1.0f,
			0.20f, -0.60f, 0.0f, 1.0f, 1.0f, 1.0f,
			0.025f, -0.45f, 0.0f, 0.45f, 0.5f, 1.0f,
			0.20f, -0.65f, 0.0f, 1.0f, 1.0f, 1.0f,
			0.025f, -0.50f, 0.0f, 0.45f, 0.5f, 1.0f,

			0.025f, -0.65f, 0.0f, 0.45f, 0.5f, 1.0f,
			0.15f, -0.80f, 0.0f, 1.0f, 1.0f, 1.0f,
				0.15f, -0.75f, 0.0f, 1.0f, 1.0f, 1.0f,
				0.025f, -0.65f, 0.0f, 0.45f, 0.5f, 1.0f,
				0.15f, -0.80f, 0.0f, 1.0f, 1.0f, 1.0f,
				0.025f, -0.70f, 0.0f, 0.45f, 0.5f, 1.0f,

				-0.025f, -0.45f, 0.0f, 0.45f, 0.5f, 1.0f,
				-0.20f, -0.65f, 0.0f, 1.0f, 1.0f, 1.0f,
				-0.20f, -0.60f, 0.0f, 1.0f, 1.0f, 1.0f,
				-0.025f, -0.45f, 0.0f, 0.45f, 0.5f, 1.0f,
				-0.20f, -0.65f, 0.0f, 1.0f, 1.0f, 1.0f,
				-0.025f, -0.50f, 0.0f, 0.45f, 0.5f, 1.0f,

				-0.025f, -0.65f, 0.0f, 0.45f, 0.5f, 1.0f,
				-0.15f, -0.80f, 0.0f, 1.0f, 1.0f, 1.0f,
				-0.15f, -0.75f, 0.0f, 1.0f, 1.0f, 1.0f,
				-0.025f, -0.65f, 0.0f, 0.45f, 0.5f, 1.0f,
				-0.15f, -0.80f, 0.0f, 1.0f, 1.0f, 1.0f,
				-0.025f, -0.70f, 0.0f, 0.45f, 0.5f, 1.0f,


				0.025f, 0.45f, 0.0f, 0.45f, 0.5f, 1.0f,
				0.20f, 0.65f, 0.0f, 1.0f, 1.0f, 1.0f,
				0.20f, 0.60f, 0.0f, 1.0f, 1.0f, 1.0f,
				0.025f, 0.45f, 0.0f, 0.45f, 0.5f, 1.0f,
				0.20f, 0.65f, 0.0f, 1.0f, 1.0f, 1.0f,
				0.025f, 0.50f, 0.0f, 0.45f, 0.5f, 1.0f,

				0.025f, 0.65f, 0.0f, 0.45f, 0.5f, 1.0f,
				0.15f, 0.80f, 0.0f, 1.0f, 1.0f, 1.0f,
				0.15f, 0.75f, 0.0f, 1.0f, 1.0f, 1.0f,
				0.025f, 0.65f, 0.0f, 0.45f, 0.5f, 1.0f,
				0.15f, 0.80f, 0.0f, 1.0f, 1.0f, 1.0f,
				0.025f, 0.70f, 0.0f, 0.45f, 0.5f, 1.0f,

				-0.025f, 0.45f, 0.0f, 0.45f, 0.5f, 1.0f,
				-0.20f, 0.65f, 0.0f, 1.0f, 1.0f, 1.0f,
				-0.20f, 0.60f, 0.0f, 1.0f, 1.0f, 1.0f,
				-0.025f, 0.45f, 0.0f, 0.45f, 0.5f, 1.0f,
				-0.20f, 0.65f, 0.0f, 1.0f, 1.0f, 1.0f,
				-0.025f, 0.50f, 0.0f, 0.45f, 0.5f, 1.0f,

				-0.025f, 0.65f, 0.0f, 0.45f, 0.5f, 1.0f,
				-0.15f, 0.80f, 0.0f, 1.0f, 1.0f, 1.0f,
				-0.15f, 0.75f, 0.0f, 1.0f, 1.0f, 1.0f,
				-0.025f, 0.65f, 0.0f, 0.45f, 0.5f, 1.0f,
				-0.15f, 0.80f, 0.0f, 1.0f, 1.0f, 1.0f,
				-0.025f, 0.70f, 0.0f, 0.45f, 0.5f, 1.0f,

				0.8f, 0.025f, 0.0f, 0.45f, 0.5f, 1.0f,
				0.85f, 0.0f, 0.0f, 0.45f, 0.5f, 1.0f,
				0.8f, -0.025f, 0.0f, 0.45f, 0.5f, 1.0f,

				-0.8f, 0.025f, 0.0f, 0.45f, 0.5f, 1.0f,
				-0.85f, 0.0f, 0.0f, 0.45f, 0.5f, 1.0f,
				-0.8f, -0.025f, 0.0f, 0.45f, 0.5f, 1.0f,

				0.58f, -0.53f, 0.0f, 0.45f, 0.5f, 1.0f,
				0.60f, -0.60f, 0.0f, 0.45f, 0.5f, 1.0f,
				0.53f, -0.58f, 0.0f, 0.45f, 0.5f, 1.0f,

				0.58f, 0.53f, 0.0f, 0.45f, 0.5f, 1.0f,
				0.60f, 0.60f, 0.0f, 0.45f, 0.5f, 1.0f,
				0.53f, 0.58f, 0.0f, 0.45f, 0.5f, 1.0f,

				-0.58f, -0.53f, 0.0f, 0.45f, 0.5f, 1.0f,
				-0.60f, -0.60f, 0.0f, 0.45f, 0.5f, 1.0f,
				-0.53f, -0.58f, 0.0f, 0.45f, 0.5f, 1.0f,

				-0.58f, 0.53f, 0.0f, 0.45f, 0.5f, 1.0f,
				-0.60f, 0.60f, 0.0f, 0.45f, 0.5f, 1.0f,
				-0.53f, 0.58f, 0.0f, 0.45f, 0.5f, 1.0f,

				0.025f, -0.80f, 0.0f, 0.45f, 0.5f, 1.0f,
				0.00f, -0.85f, 0.0f, 0.45f, 0.5f, 1.0f,
				-0.025f, -0.80f, 0.0f, 0.45f, 0.5f, 1.0f,

				0.025f, 0.80f, 0.0f, 0.45f, 0.5f, 1.0f,
				0.00f, 0.85f, 0.0f, 0.45f, 0.5f, 1.0f,
				-0.025f, 0.80f, 0.0f, 0.45f, 0.5f, 1.0f
	};
	glm::vec3 Positions[] = {
glm::vec3(0.75f,  0.0f,  0.0f),
glm::vec3(1.0f,  1.0f, -1.0f),
glm::vec3(-1.5f, 0.0f, -2.0f),
glm::vec3(-3.8f, 3.0f, -3.5f),
glm::vec3(2.4f, 0.0f, -4.0f),
	};
	float y_up[] = {
		1.4f, 1.87f, 2.33f, 2.8f, 3.27f
	};
	float y_down[] = {
		-1.2f, -1.6f, -2.0f, -2.4f, -2.8f
	};

	unsigned int VAO, VBO, EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices1), vertices1, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glEnable(GL_DEPTH_TEST);
	while (!glfwWindowShouldClose(window))
	{
		processInput(window);
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		glClearColor(0.75f, 0.75f, 0.75f, 1.0f);
		//glClear(GL_COLOR_BUFFER_BIT);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		ourShader.use();

		glm::mat4 view;
		view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
		ourShader.setMat4("view", view);
		glm::mat4 projection = glm::mat4(1.0f);
		projection = glm::perspective(glm::radians(fov), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
		ourShader.setMat4("projection", projection);


		ourShader.use();

		for (unsigned int i = 0; i < 5; i++)
		{
			glm::mat4 model(1.0f);
			unsigned int modelLoc = glGetUniformLocation(ourShader.ID, "model");
			/*if (Positions[i].y <= y_down[i])
			{
				uniform_real_distribution<double> u(-1, 1);
				default_random_engine e(time(NULL));
				Positions[i].x = u(e);
				Positions[i].y = y_up[i];
			}
			else
			{
				Positions[i].y = Positions[i].y - 0.005;
			}*/

			model = glm::translate(model, Positions[i]);
			model = glm::scale(model, glm::vec3(0.25, 0.25, 1));
			model = glm::rotate(model, (float)glfwGetTime() * glm::radians(50.0f), glm::vec3(0.0f, 0.0f, 1.0f));
			ourShader.setMat4("model", model);
			glBindVertexArray(VAO);
			glDrawArrays(GL_TRIANGLES, 0, 240);
		}


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
	//glViewport(0, 0, width, height);
	int aaa = 0;
	aaa = min(width, height);
	glViewport((width-aaa)/2, (height-aaa)/2, aaa, aaa);
}

void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	float cameraSpeed = 2.5f * deltaTime;
	if (glfwGetKey(window, GLFW_KEY_PAGE_DOWN) == GLFW_PRESS)
		cameraPos += cameraSpeed * cameraFront;
	if (glfwGetKey(window, GLFW_KEY_PAGE_UP) == GLFW_PRESS)
		cameraPos -= cameraSpeed * cameraFront;
}