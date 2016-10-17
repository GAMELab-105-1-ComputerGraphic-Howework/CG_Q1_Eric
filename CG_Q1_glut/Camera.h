#include "Transform.h"

#pragma once
class Camera
{
private:
	const glm::vec4 forward = glm::vec4(0.0f, 0.0f, 1.0f, 1.0f);
	const glm::vec4 up = glm::vec4(0.0f, 0.0f, 1.0f, 1.0f);
public:
	Camera();
	~Camera();
	glm::mat4 getView();
	Transform transform;
};

