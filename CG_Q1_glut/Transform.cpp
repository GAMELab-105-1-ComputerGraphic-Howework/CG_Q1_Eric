#include "Transform.h"



Transform::Transform()
{
	this->rotation = glm::mat4();
	this->position = glm::vec3(0.0f, 0.0f, 0.0f);
}

Transform::Transform(glm::vec3 position, glm::mat4 rotation)
{
	this->rotation = rotation;
	this->position = position;
}


Transform::~Transform()
{
}

void Transform::rotate(GLfloat angle_degree, glm::vec3 axis3, ROTATE_SPACE space) {
	if (space == ROTATE_SPACE::WORLD) {
		glm::vec4 axis4 = glm::vec4(axis3, 0.0f);
		axis4 = axis4 * rotation;
		axis3 = glm::vec3(axis4.x, axis4.y, axis4.z);
	}
	rotation = glm::rotate(rotation, glm::radians(angle_degree), glm::vec3(axis3.x, axis3.y, axis3.z));
}

glm::mat4 Transform::getTransform() {
	glm::mat4 transform;
	transform =  rotation * glm::translate(transform, position);
	return transform;
}