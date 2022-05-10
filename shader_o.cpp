#include <iostream>
#include "shader_o.h"

Shader::Shader(const GLchar* vSourcePath, const GLchar* fSourcePath_1, const GLchar* fSourcePath_2) {
	const char* vShaderSource = ReadShader(vSourcePath);
	const char* fShaderSource_1 = ReadShader(fSourcePath_1);
	const char* fShaderSource_2 = ReadShader(fSourcePath_2);
	

	//������ɫ��
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER); 
	glShaderSource(vertexShader, 1, &vShaderSource, NULL);  
	glCompileShader(vertexShader);

	//ƬԪ��ɫ��1
	GLuint fragmentShader_1 = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader_1, 1, &fShaderSource_1, NULL);
	glCompileShader(fragmentShader_1);


	//ƬԪ��ɫ��2
	GLuint fragmentShader_2 = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader_2, 1, &fShaderSource_2, NULL);
	glCompileShader(fragmentShader_2);

	//��ɫ������1
	shaderProgramId[0] = glCreateProgram();

	//������ɫ��1
	glAttachShader(shaderProgramId[0], vertexShader);	
	glAttachShader(shaderProgramId[0], fragmentShader_1);
	glLinkProgram(shaderProgramId[0]);
	//���Ӽ��
	GLint success;
	char infolog[512];
	glGetProgramiv(shaderProgramId[0], GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderProgramId[0], 512, NULL, infolog);
		std::cerr << "Shader program linking failed. " << infolog << std::endl;
	}

	//��ɫ������2
	shaderProgramId[1] = glCreateProgram();

	//������ɫ��2
	glAttachShader(shaderProgramId[1], vertexShader);
	glAttachShader(shaderProgramId[1], fragmentShader_2);
	glLinkProgram(shaderProgramId[1]);
	//���Ӽ��
	glGetProgramiv(shaderProgramId[1], GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderProgramId[1], 512, NULL, infolog);
		std::cerr << "Shader program linking failed. " << infolog << std::endl;
	}
	
	//ɾ����ɫ��
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader_1);
	glDeleteShader(fragmentShader_2);
}

const GLchar* Shader::ReadShader(const char* filename)
{
	FILE* infile = NULL;
	fopen_s(&infile, filename, "rb");
	if (!infile) {
		std::cerr << "Unable to open file '" << filename << "'" << std::endl;
		return NULL;
	}
	fseek(infile, 0, SEEK_END);
	size_t len = ftell(infile);
	fseek(infile, 0, SEEK_SET);
	GLchar* source = new GLchar[len + 1];
	fread(source, 1, len, infile);
	fclose(infile);
	source[len] = '\0';
	return const_cast<const GLchar*>(source);
}


