#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "shader_m.h"
#include "camera.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

//窗口回调函数
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
unsigned int loadTexture(char const* path);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;
float mixValue = 0.0f;
// camera
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

glm::vec3 lightPos(1.2f, 1.0f, -1.0f);

bool firstMouse = true;
float yaw = -90.0f;	// yaw is initialized to -90.0 degrees since a yaw of 0.0 results in a direction vector pointing to the right so we initially rotate a bit to the left.
float pitch = 0.0f;
float lastX = 800.0f / 2.0;
float lastY = 600.0 / 2.0;
float fov = 45.0f;

float deltaTime = 0.0f; // 当前帧与上一帧的时间差
float lastFrame = 0.0f; // 上一帧的时间

int main()
{
    glfwInit();//初始化glfw
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);//配置glfw，主版本号(Major)和次版本号(Minor)
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Texture", NULL, NULL);
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);
    // tell GLFW to capture our mouse
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);//初始化GLAD

    Shader houseShader("shaders/house.vs", "shaders/house.fs");
    Shader backgroundShader("shaders/night.vs", "shaders/night.fs");
    //Shader groundShader("shaders/ground.vs", "shaders/ground.fs");
    //Shader wallShader("shaders/ground.vs", "shaders/ground.fs");
    float vertices[] = {
        //底面
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,  0.0f, 0.0f, -1.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 0.0f,  0.0f, 0.0f, -1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,  0.0f, 0.0f, -1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,  0.0f, 0.0f, -1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,  0.0f, 0.0f, -1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,  0.0f, 0.0f, -1.0f,
        //顶面
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,  0.0f, 0.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,  0.0f, 0.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,  0.0f, 0.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,  0.0f, 0.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,  0.0f, 0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,  0.0f, 0.0f, 1.0f,
        //左面
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,  -1.0f, 0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 0.0f,  -1.0f, 0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  1.0f, 1.0f,  -1.0f, 0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  1.0f, 1.0f,  -1.0f, 0.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 1.0f,  -1.0f, 0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,  -1.0f, 0.0f, 0.0f,
        //右面
         0.5f,  0.5f,  0.5f,  0.0f, 0.0f,  1.0f, 0.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 0.0f,  1.0f, 0.0f, 0.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 1.0f,  1.0f, 0.0f, 0.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 1.0f,  1.0f, 0.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  0.0f, 1.0f,  1.0f, 0.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  0.0f, 0.0f,  1.0f, 0.0f, 0.0f,
         //后面
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,  0.0f, -1.0f, 0.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 1.0f,  0.0f, -1.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,  0.0f, -1.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,  0.0f, -1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,  0.0f, -1.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,  0.0f, -1.0f, 0.0f,
        //前面
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,  0.0f, 1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,  0.0f, 1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,  0.0f, 1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,  0.0f, 1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,  0.0f, 1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,  0.0f, 1.0f, 0.0f
    };
    float ground_vertices[] = {
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
         0.5f, -0.5f, -0.5f,  3.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  3.0f, 3.0f,
         0.5f,  0.5f, -0.5f,  3.0f, 3.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 3.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f
    };
    float door_vertices[] = {
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f
    };
    float roof_vertices[] = {
        0.0f, 0.5f, 0.0f,  0.5f, 1.0f,
        0.5f, 0.0f, 0.5f,  0.0f, 0.0f,
        0.5f, 0.0f, -0.5f, 1.0f, 0.0f
    };
    glm::vec3 cubePositions[] = {
    glm::vec3(0.0f,  0.0f,  0.0f),
    glm::vec3(2.0f,  5.0f, -15.0f),
    glm::vec3(-1.5f, -2.2f, -2.5f),
    glm::vec3(-3.8f, -2.0f, -12.3f),
    glm::vec3(2.4f, -0.4f, -3.5f),
    glm::vec3(-1.7f,  3.0f, -7.5f),
    glm::vec3(1.3f, -2.0f, -2.5f),
    glm::vec3(1.5f,  2.0f, -2.5f),
    glm::vec3(1.5f,  0.2f, -1.5f),
    glm::vec3(-1.3f,  1.0f, -1.5f)
    };

    unsigned int houseVAO, houseVBO;
    glGenVertexArrays(1, &houseVAO);
    glGenBuffers(1, &houseVBO);

    glBindVertexArray(houseVAO);
    glBindBuffer(GL_ARRAY_BUFFER, houseVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // color attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    // normal attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(5 * sizeof(float)));
    glEnableVertexAttribArray(2);

    unsigned int groundVAO, groundVBO;
    glGenVertexArrays(1, &groundVAO);
    glGenBuffers(1, &groundVBO);

    glBindVertexArray(groundVAO);
    glBindBuffer(GL_ARRAY_BUFFER, groundVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(ground_vertices), ground_vertices, GL_STATIC_DRAW);
    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // color attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    unsigned int doorVAO, doorVBO;
    glGenVertexArrays(1, &doorVAO);
    glGenBuffers(1, &doorVBO);
    glBindVertexArray(doorVAO);
    glBindBuffer(GL_ARRAY_BUFFER, doorVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(door_vertices), door_vertices, GL_STATIC_DRAW);
    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // color attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    unsigned int roofVAO, roofVBO;
    glGenVertexArrays(1, &roofVAO);
    glGenBuffers(1, &roofVBO);
    glBindVertexArray(roofVAO);
    glBindBuffer(GL_ARRAY_BUFFER, roofVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(roof_vertices), roof_vertices, GL_STATIC_DRAW);
    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // color attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    stbi_set_flip_vertically_on_load(true);

    unsigned int house_texture = loadTexture("resources/textures/wall3.jpg");

    unsigned int ground_texture = loadTexture("resources/textures/ground1.jpg");

    unsigned int wall_texture = loadTexture("resources/textures/wall2.png");

    unsigned int door_texture = loadTexture("resources/textures/door0.jpg");

    unsigned int window_texture = loadTexture("resources/textures/window1.jpg");

    unsigned int roof_texture = loadTexture("resources/textures/roof1.jpg");

    unsigned int top_texture = loadTexture("resources/textures/top1.jpg");

    unsigned int left_texture = loadTexture("resources/textures/left1.jpg");

    unsigned int front_texture = loadTexture("resources/textures/front1.jpg");

    unsigned int right_texture = loadTexture("resources/textures/right1.jpg");

    unsigned int back_texture = loadTexture("resources/textures/back1.jpg");

    unsigned int nightsky_texture = loadTexture("resources/textures/night1.jpg");

    unsigned int night_texture = loadTexture("resources/textures/night0.jpg");

    unsigned int bottom_texture = loadTexture("resources/textures/bottom0.jpg");

    unsigned int nightbottom_texture = loadTexture("resources/textures/bottom1.jpg");


    houseShader.use();
    houseShader.setInt("material.diffuse", 0);
    backgroundShader.use();
    backgroundShader.setInt("texture1", 0);
    backgroundShader.setInt("texture2", 1);
    glEnable(GL_DEPTH_TEST);
    float day = -0.5f;
    bool nightTOday = true;
    while (!glfwWindowShouldClose(window))
    {


        if (day > 1.5 || day < -0.5)
        {
                nightTOday = !nightTOday;
        }

        if (nightTOday)
            day = day + 0.001;
        else
            day = day - 0.001;
        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        processInput(window);

        glClearColor(day, day, day, 1.0f);
        //glClear(GL_COLOR_BUFFER_BIT);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, house_texture);
 
        houseShader.use();
        houseShader.setVec3("light.position", lightPos);
        houseShader.setVec3("viewPos", camera.Position);

        // light properties
        if (day < 0.2)
            houseShader.setVec3("light.ambient", 0.2f, 0.2f, 0.2f);
        else if (day > 0.9)
            houseShader.setVec3("light.ambient", 0.9f, 0.9f, 0.9f);
        else
            houseShader.setVec3("light.ambient", day, day, day);
        houseShader.setVec3("light.diffuse", 0.5f, 0.5f, 0.5f);
        houseShader.setVec3("light.specular", 1.0f, 1.0f, 1.0f);

        // material properties
        houseShader.setVec3("material.specular", 0.5f, 0.5f, 0.5f);
        houseShader.setFloat("material.shininess", 64.0f);
        // view/projection transformations
        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        glm::mat4 view = camera.GetViewMatrix();
        houseShader.setMat4("projection", projection);
        houseShader.setMat4("view", view);
        // world transformation
        glm::mat4 model = glm::mat4(1.0f);
        //model = glm::rotate(model, glm::radians(45.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        houseShader.setMat4("model", model);
        glBindVertexArray(houseVAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        //地板
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, ground_texture);
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, -0.99f, 0.0f));
        model = glm::rotate(model, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        houseShader.setMat4("model", model);
        glBindVertexArray(groundVAO);
        glDrawArrays(GL_TRIANGLES, 0, 6);


        // 天花板
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, wall_texture);
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, -0.01f, 0.0f));
        model = glm::rotate(model, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        //model = glm::scale(model, glm::vec3(0.98f, 0.98f, 1.0f));
        houseShader.setMat4("model", model);
        glBindVertexArray(groundVAO);
        glDrawArrays(GL_TRIANGLES, 0, 6);
        //墙壁
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, 0.00f, 0.01f));
        //model = glm::rotate(model, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        houseShader.setMat4("model", model);
        glBindVertexArray(groundVAO);
        glDrawArrays(GL_TRIANGLES, 0, 6);

        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.01f, 0.0f, 0.0f));
        model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        houseShader.setMat4("model", model);
        glBindVertexArray(groundVAO);
        glDrawArrays(GL_TRIANGLES, 0, 6);

        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.99f, 0.0f, 0.0f));
        model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        houseShader.setMat4("model", model);
        glBindVertexArray(groundVAO);
        glDrawArrays(GL_TRIANGLES, 0, 6);

        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.99f));
        houseShader.setMat4("model", model);
        glBindVertexArray(groundVAO);
        glDrawArrays(GL_TRIANGLES, 0, 6);

        //门
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, door_texture);
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, -0.18f, 1.01f));
        //model = glm::rotate(model, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        model = glm::scale(model, glm::vec3(0.35f, 0.63f, 1.0f));
        houseShader.setMat4("model", model);
        glBindVertexArray(doorVAO);
        glDrawArrays(GL_TRIANGLES, 0, 6);
        //窗
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, window_texture);
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(-0.01f, 0.0f, 0.0f));
        model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        model = glm::scale(model, glm::vec3(0.35f, 0.35f, 1.0f));
        houseShader.setMat4("model", model);
        glBindVertexArray(doorVAO);
        glDrawArrays(GL_TRIANGLES, 0, 6);
        //屋顶
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, roof_texture);
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, 0.5f, 0.0f));
        //model = glm::rotate(model, glm::radians(90.0f), glm::vec3(-1.0f, 0.0f, 0.0f));
        //model = glm::scale(model, glm::vec3(0.35f, 0.35f, 1.0f));
        houseShader.setMat4("model", model);
        glBindVertexArray(roofVAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        //model = glm::scale(model, glm::vec3(0.35f, 0.35f, 1.0f));
        houseShader.setMat4("model", model);
        glBindVertexArray(roofVAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        houseShader.setMat4("model", model);
        glBindVertexArray(roofVAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        houseShader.setMat4("model", model);
        glBindVertexArray(roofVAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);


        backgroundShader.use();
        if(day > 1.0)
            backgroundShader.setFloat("alpha", 1.0);
        else if (day < 0.0)
            backgroundShader.setFloat("alpha", 0.0);
        else
            backgroundShader.setFloat("alpha", day);
        backgroundShader.setMat4("projection", projection);
        backgroundShader.setMat4("view", view);
        //top
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, top_texture);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, nightsky_texture);
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, 9.0f, 0.0f));
        model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        model = glm::scale(model, glm::vec3(15.0f, 15.0f, 1.0f));
        backgroundShader.setMat4("model", model);
        glBindVertexArray(doorVAO);
        glDrawArrays(GL_TRIANGLES, 0, 6);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, left_texture);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, night_texture);
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(-7.0f, 4.0f, 0.0f));
        model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        model = glm::scale(model, glm::vec3(15.0f, 9.0f, 1.0f));
        backgroundShader.setMat4("model", model);
        glBindVertexArray(doorVAO);
        glDrawArrays(GL_TRIANGLES, 0, 6);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, front_texture);
        //glActiveTexture(GL_TEXTURE1);
        //glBindTexture(GL_TEXTURE_2D, night_texture);
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, 4.0f, -7.0f));
        //model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        model = glm::scale(model, glm::vec3(15.0f, 9.0f, 1.0f));
        backgroundShader.setMat4("model", model);
        glBindVertexArray(doorVAO);
        glDrawArrays(GL_TRIANGLES, 0, 6);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, right_texture);
        //glActiveTexture(GL_TEXTURE1);
        //glBindTexture(GL_TEXTURE_2D, night_texture);
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(7.0f, 4.0f, 0.0f));
        model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, -1.0f, 0.0f));
        model = glm::scale(model, glm::vec3(15.0f, 9.0f, 1.0f));
        backgroundShader.setMat4("model", model);
        glBindVertexArray(doorVAO);
        glDrawArrays(GL_TRIANGLES, 0, 6);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, back_texture);
        //glActiveTexture(GL_TEXTURE1);
        //glBindTexture(GL_TEXTURE_2D, night_texture);
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, 4.0f, 7.0f));
        model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        model = glm::scale(model, glm::vec3(15.0f, 9.0f, 1.0f));
        backgroundShader.setMat4("model", model);
        glBindVertexArray(doorVAO);
        glDrawArrays(GL_TRIANGLES, 0, 6);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, bottom_texture);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, nightbottom_texture);
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, -1.0f, 0.0f));
        model = glm::rotate(model, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        model = glm::scale(model, glm::vec3(15.0f, 15.0f, 1.0f));
        backgroundShader.setMat4("model", model);
        glBindVertexArray(doorVAO);
        glDrawArrays(GL_TRIANGLES, 0, 6);


        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glDeleteVertexArrays(1, &houseVAO);
    glDeleteBuffers(1, &houseVBO);
    glDeleteVertexArrays(1, &groundVAO);
    glDeleteBuffers(1, &groundVBO);
    glDeleteVertexArrays(1, &doorVAO);
    glDeleteBuffers(1, &doorVBO);
    glDeleteVertexArrays(1, &roofVAO);
    glDeleteBuffers(1, &roofVBO);
    std::cout << day << std::endl;
    glfwTerminate();
    return 0;
}

void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.ProcessKeyboard(FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.ProcessKeyboard(LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.ProcessKeyboard(RIGHT, deltaTime);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}


// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{
    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);

    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

    lastX = xpos;
    lastY = ypos;

    camera.ProcessMouseMovement(xoffset, yoffset);
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    camera.ProcessMouseScroll(static_cast<float>(yoffset));
}

unsigned int loadTexture(char const* path)
{
    unsigned int textureID;
    glGenTextures(1, &textureID);

    int width, height, nrComponents;
    unsigned char* data = stbi_load(path, &width, &height, &nrComponents, 0);
    if (data)
    {
        GLenum format;
        if (nrComponents == 1)
            format = GL_RED;
        else if (nrComponents == 3)
            format = GL_RGB;
        else if (nrComponents == 4)
            format = GL_RGBA;

        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        stbi_image_free(data);
    }
    else
    {
        std::cout << "Texture failed to load at path: " << path << std::endl;
        stbi_image_free(data);
    }

    return textureID;
}