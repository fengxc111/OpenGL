#include "shader_o.h"

// 06.cpp画两个不同颜色的三角形。
// 通过2个VAO和2个VBO实现两个三角形。
// 通过2个片元着色器使得2个三角形不同颜色。

void userInit();									//自定义初始化
void reshape(int w, int h);							//重绘
void display(void);

GLuint vboId[2];
GLuint vaoId[2];

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(800, 600);
	glutCreateWindow("示例");
	glewInit();
	userInit();
	//重绘函数
	glutReshapeFunc(reshape);
	//绘制回调函数
	glutDisplayFunc(display);
	glutMainLoop();
	return 0;
}

//自定义初始化函数    
void userInit()
{
	//创建顶点数据    
	const GLfloat vertices[] = {
		//第一个三角形
		-0.9f, -0.5f, 0.0f,
		0.0f, -0.5f, 0.0f,
		-0.45f, 0.5f, 0.0f,
		//第二个三角形
		0.0f, -0.5f, 0.0f,
		0.9f, -0.5f, 0.0f,
		0.45f, 0.5f, 0.0f,
	};

	//创建VAO对象
	glGenVertexArrays(2, vaoId);
	glBindVertexArray(vaoId[0]);
	glBindVertexArray(vaoId[1]);
	//创建VBO对象	
	glGenBuffers(2, vboId);
	glBindBuffer(GL_ARRAY_BUFFER, vboId[0]);
	//传入VBO数据
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices) / 2, vertices, GL_STATIC_DRAW);
	//解除VBO绑定
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	//创建VBO对象	
	glBindBuffer(GL_ARRAY_BUFFER, vboId[1]);
	//传入VBO数据
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices) / 2, &vertices[9], GL_STATIC_DRAW);
	//解除VBO绑定
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

//调整窗口大小回调函数    
void reshape(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
}

//绘制回调函数    
void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);

	//创建着色器
	Shader shader("shader/vShaderSource.glsl", "shader/fShaderSource.glsl", "shader/fShaderSource_o.glsl");

	//使用着色器1
	shader.use(1);
	glBindBuffer(GL_ARRAY_BUFFER, vboId[0]);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glDrawArrays(GL_TRIANGLES, 0, 3);

	//使用着色器2
	shader.use(2);
	glBindBuffer(GL_ARRAY_BUFFER, vboId[1]);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glDrawArrays(GL_TRIANGLES, 0, 3);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glDisableVertexAttribArray(0);
	glutSwapBuffers();
}
