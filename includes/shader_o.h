#ifndef SHADER_H
#define SHADER_H

// ���Ӿ�̬�⣬�����ȶ���GLEW_STATIC 
#define GLEW_STATIC

#include <GL/glew.h>  
#include <GL/freeglut.h>  
#include <GLFW/glfw3.h>

class Shader
{
public:
	// ����ɫ���ļ�
	const GLchar* ReadShader(const char* filename);
	// ���캯��
	Shader(const GLchar* vSourcePath, const GLchar* fSourcePath_1, const GLchar* fSourcePath_2);
	// ʹ����ɫ������
	void use(GLuint f) {
		if (f == 1)
			glUseProgram(shaderProgramId[0]);
		else if (f == 2)
			glUseProgram(shaderProgramId[1]);
	}

private:
	// ��ɫ������id
	GLuint shaderProgramId[2];
};
#endif

