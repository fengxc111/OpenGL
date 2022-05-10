#include "shader_o.h"

// 06.cpp��������ͬ��ɫ�������Ρ�
// ͨ��2��VAO��2��VBOʵ�����������Ρ�
// ͨ��2��ƬԪ��ɫ��ʹ��2�������β�ͬ��ɫ��

void userInit();									//�Զ����ʼ��
void reshape(int w, int h);							//�ػ�
void display(void);

GLuint vboId[2];
GLuint vaoId[2];

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(800, 600);
	glutCreateWindow("ʾ��");
	glewInit();
	userInit();
	//�ػ溯��
	glutReshapeFunc(reshape);
	//���ƻص�����
	glutDisplayFunc(display);
	glutMainLoop();
	return 0;
}

//�Զ����ʼ������    
void userInit()
{
	//������������    
	const GLfloat vertices[] = {
		//��һ��������
		-0.9f, -0.5f, 0.0f,
		0.0f, -0.5f, 0.0f,
		-0.45f, 0.5f, 0.0f,
		//�ڶ���������
		0.0f, -0.5f, 0.0f,
		0.9f, -0.5f, 0.0f,
		0.45f, 0.5f, 0.0f,
	};

	//����VAO����
	glGenVertexArrays(2, vaoId);
	glBindVertexArray(vaoId[0]);
	glBindVertexArray(vaoId[1]);
	//����VBO����	
	glGenBuffers(2, vboId);
	glBindBuffer(GL_ARRAY_BUFFER, vboId[0]);
	//����VBO����
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices) / 2, vertices, GL_STATIC_DRAW);
	//���VBO��
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	//����VBO����	
	glBindBuffer(GL_ARRAY_BUFFER, vboId[1]);
	//����VBO����
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices) / 2, &vertices[9], GL_STATIC_DRAW);
	//���VBO��
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

//�������ڴ�С�ص�����    
void reshape(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
}

//���ƻص�����    
void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);

	//������ɫ��
	Shader shader("shader/vShaderSource.glsl", "shader/fShaderSource.glsl", "shader/fShaderSource_o.glsl");

	//ʹ����ɫ��1
	shader.use(1);
	glBindBuffer(GL_ARRAY_BUFFER, vboId[0]);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glDrawArrays(GL_TRIANGLES, 0, 3);

	//ʹ����ɫ��2
	shader.use(2);
	glBindBuffer(GL_ARRAY_BUFFER, vboId[1]);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glDrawArrays(GL_TRIANGLES, 0, 3);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glDisableVertexAttribArray(0);
	glutSwapBuffers();
}
