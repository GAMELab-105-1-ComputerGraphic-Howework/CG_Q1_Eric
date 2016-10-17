#include "Shader.h"

Shader::Shader(string name) {

	string vsCodeStr;
	string fsCodeStr;

	ifstream vsFile;
	ifstream fsFile;

	vsFile.exceptions(ifstream::badbit);
	fsFile.exceptions(ifstream::badbit);

	try {
		vsFile.open("Shaders/" + name + "/vs.glsl");
		fsFile.open("Shaders/" + name + "/fs.glsl");

		stringstream vsSStream, fsSStream;

		vsSStream << vsFile.rdbuf();
		fsSStream << fsFile.rdbuf();

		vsFile.close();
		fsFile.close();

		vsCodeStr = vsSStream.str();
		fsCodeStr = fsSStream.str();

	}
	catch (ifstream::failure e) {
		cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << endl;
	}


	const char * vsCode = vsCodeStr.c_str();
	const char * fsCode = fsCodeStr.c_str();

	// ½sÄ¶µÛ¦â¾¹
	GLuint vs, fs;
	GLint success;
	char infoLog[512];

	// vs
	vs = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vs, 1, &vsCode, NULL);
	glCompileShader(vs);

	glGetShaderiv(vs, GL_COMPILE_STATUS, &success);

	if (!success) {
		glGetShaderInfoLog(vs, 512, NULL, infoLog);
		cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << endl;
	}

	// fs
	fs = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fs, 1, &fsCode, NULL);
	glCompileShader(fs);

	glGetShaderiv(fs, GL_COMPILE_STATUS, &success);

	if (!success) {
		glGetShaderInfoLog(fs, 512, NULL, infoLog);
		cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << endl;
	}

	this->program = glCreateProgram();
	glAttachShader(this->program, vs);
	glAttachShader(this->program, fs);
	glLinkProgram(this->program);

	glGetProgramiv(this->program, GL_LINK_STATUS, &success);

	if (!success) {
		glGetProgramInfoLog(this->program, 512, NULL, infoLog);
		cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << endl;
	}

	glDeleteShader(vs);
	glDeleteShader(fs);
}

void Shader::use() {
	glUseProgram(this->program);
}