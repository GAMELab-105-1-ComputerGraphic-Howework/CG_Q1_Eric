#include "Star.h"

Star::Star()
{
	shader = new Shader("Star");

	glGenBuffers(1, &EBO);
	glGenBuffers(1, &VBO);

	glGenVertexArrays(1, &VAO);

	glBindVertexArray(VAO);

	{
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
		glEnableVertexAttribArray(0);
	}

	glBindVertexArray(0);
}

void Star::render(glm::mat4 & view, glm::mat4 & projection) {
	this->shader->use();

	glBindVertexArray(VAO);

	GLint modelLoc = glGetUniformLocation(this->shader->program, "model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(transform.getTransform()));

	modelLoc = glGetUniformLocation(this->shader->program, "view");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(view));

	modelLoc = glGetUniformLocation(this->shader->program, "projection");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(projection));

	glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(float), GL_UNSIGNED_INT, 0);

	glBindVertexArray(VAO);
}


Star::~Star()
{
}
