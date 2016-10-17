#ifndef GL_INCLUDE
#define GL_INCLUDE
// GLEW
#include <GL/glew.h>
// GLUT
#include <GL/glut.h>
#endif

#ifndef GLM_INCLUDE
#define GLM_INCLUDE
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#endif

class Transform
{
	
private: 
	glm::mat4 rotation;
	glm::vec3 position;
public:
	enum ROTATE_SPACE
	{
		WORLD, LOCAL
	};
	Transform();
	Transform(glm::vec3 position, glm::mat4 rotation);

	~Transform();
	void rotate(GLfloat angle_degree, glm::vec3 axis, ROTATE_SPACE space);
	glm::mat4 getTransform();
};

