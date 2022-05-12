//��ϰ
//1.�޸Ķ�����ɫ�������������µߵ����ο����
//2.ʹ��uniform����һ��ˮƽƫ�������ڶ�����ɫ����ʹ�����ƫ�������������ƶ�����Ļ�Ҳࣺ�ο����
//3.ʹ��out�ؼ��ְѶ���λ�������Ƭ����ɫ��������Ƭ�ε���ɫ����Ϊ�붥��λ����ȣ�������������λ��ֵ��������
//���б���ֵ�Ľ������������Щ�󣬳��Իش���������⣺Ϊʲô�������ε����½��Ǻڵ� ? ���ο����
//******Tips�۲춥������(vertices2[])

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

//���ڻص�����
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
//"layout (location = 1) in vec3 aColor;\n"
"layout (location = 0) in vec3 aColor;\n"//��ϰ3
//"out vec4 vertexColor;\n"
"out vec3 ourColor;\n"
"uniform float dx;\n"
"void main()\n"
"{\n"
//"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
//"   gl_Position = vec4(aPos.x, -aPos.y, aPos.z, 1.0);\n"//��ϰ1
"   gl_Position = vec4(aPos.x + dx, -aPos.y, aPos.z, 1.0);\n"//��ϰ2
//"   gl_Position = vec4(aPos, 1.0);\n"
//"   vertexColor = vec4(0.5f, 0.0f, 0.0f, 1.0f);\n"
"   ourColor = aColor;\n"
"}\0";

const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
//"in vec4 vertexColor;\n"
//"uniform vec4 ourColor;\n"
"in vec3 ourColor;\n"
"void main()\n"
"{\n"
//"    FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
//"    FragColor = vertexColor;\n"
"    FragColor = vec4(ourColor, 1.0);\n"
"}\0";

int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    GLFWwindow* window = glfwCreateWindow(800, 600, "Shader & GLSL", NULL, NULL);
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
    //������ɫ��
    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    //Ƭ����ɫ��
    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    //��ɫ������
    unsigned int shaderProgram;
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    glUseProgram(shaderProgram);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    float vertices[] = {
        /*-0.5f, -0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
         0.0f,  0.5f, 0.0f*/
        0.5f, 0.5f, 0.0f,   // ���Ͻ�
        0.5f, -0.5f, 0.0f,  // ���½�
        -0.5f, -0.5f, 0.0f, // ���½�
        -0.5f, 0.5f, 0.0f   // ���Ͻ�
    };

    //unsigned int indices[] = { // ע��������0��ʼ! 
    //0, 1, 3, // ��һ��������
    //1, 2, 3  // �ڶ���������
    //};
    //��ϰ1��������
    float vertices1[] = {
        -0.5f, 0.5f, 0.0f,
        -0.5f, 0.0f, 0.0f,
        0.0f, 0.5f, 0.0f,

        0.5f, -0.5f, 0.0f,
        0.5f, 0.0f, 0.0f,
        0.0f, -0.5f, 0.0f
    };

    float vertices2[] = {
        // λ��              // ��ɫ
         0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   // ����
        -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   // ����
         0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f    // ����
    };

    unsigned int VAO, VBO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    //glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices2), vertices2, GL_STATIC_DRAW);

    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    //glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    //glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    //glEnableVertexAttribArray(0);
    // 
    // λ������
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // ��ɫ����
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    //glViewport(0, 0, 800, 600);

    // glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    while (!glfwWindowShouldClose(window))
    {
        processInput(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgram);
        //glBindVertexArray(VAO);
        //glDrawArrays(GL_TRIANGLES, 0, 3);
       //// glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        //glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        // 
        //��ʱ��仯��ɫ������glsl�е�uniform
        //float timeValue = glfwGetTime();
        //float greenValue = (sin(timeValue) / 2.0f) + 0.5f;
        //int vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");
        //glUseProgram(shaderProgram);
        //glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);
        
        //��ϰ2
        float timeValue = glfwGetTime();
        float dxValue = (sin(timeValue) / 2.0f);
        int vertexColorLocation = glGetUniformLocation(shaderProgram, "dx");
        glUseProgram(shaderProgram);
        glUniform1f(vertexColorLocation, dxValue);

        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    //glDeleteBuffers(1, &EBO);
    glDeleteProgram(shaderProgram);

    glfwTerminate();
    return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);

}

void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}














