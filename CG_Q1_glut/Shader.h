#ifndef GL_INCLUDE
#define GL_INCLUDE
// GLEW
#include <GL/glew.h>
// GLUT
#include <GL/glut.h>
#endif

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;

class Shader {
public:
	GLuint program;

	Shader(string name);

	void use();
};