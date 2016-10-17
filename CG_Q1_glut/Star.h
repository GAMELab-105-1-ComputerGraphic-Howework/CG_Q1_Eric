#ifndef GL_INCLUDE
#define GL_INCLUDE
// GLEW
#include <GL/glew.h>
// GLUT
#include <GL/glut.h>
#endif

#include "Transform.h"
#include "Shader.h"

class Star
{
	GLfloat vertices[12] = {
		1.0f, 1.0f, 1.0f,
		-1.0f, 1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f, 1.0f
	};

	GLuint indices[12] = {
		0, 1, 2,
		0, 1, 3,
		0, 2, 3,
		1, 2, 3
	};

public:
	Transform transform;
	Shader * shader;
	GLuint VAO, VBO, EBO;
	Star();
	~Star();
	void render(glm::mat4 & view, glm::mat4 & projection);
};

