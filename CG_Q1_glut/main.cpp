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

#include <iostream>
#include <cmath>
#include "Star.h"

#define	PI 3.1415926

int timer_cnt;
int WIDTH = 800;
int HEIGHT = 600;

float light_position[] = { -20, 20, 0 };  //¥ú·½ªº¦ì¸m 

glm::mat4 view;
glm::mat4 projection;

Star * star;

void reshape(int w, int h) {
	WIDTH = w;
	HEIGHT = h;

	glViewport(0, 0, w, h);

	GLfloat aspectRatio = (GLfloat)w / (GLfloat)h;

	projection = glm::perspective(glm::radians(45.0f), aspectRatio, 0.1f, 100.0f);
}

bool press;
float old_x = 0, old_y = 0;

void mouse(int button, int state, int x, int y) {
	if (button == GLUT_RIGHT_BUTTON) {
		if (state == GLUT_DOWN) {
			old_x = x;
			old_y = y;
			press = true;
		}
		else {
			press = false;
		}
	}
}

void mouseMotion(int x, int y) {
	if (press == true) {

		float delta_x = (x - old_x) * 0.5f;
		float delta_y = (y - old_y) * 0.5f;
		old_x = x;
		old_y = y;

		star->transform.rotate(delta_x, glm::vec3(0.0f, 1.0f, 0.0f), Transform::ROTATE_SPACE::WORLD);
		star->transform.rotate(delta_y, glm::vec3(1.0f, 0.0f, 0.0f), Transform::ROTATE_SPACE::WORLD);
	}
}

void display() {
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	float t = timer_cnt / 100.0f;
	
	star->render(view, projection);

 	glutSwapBuffers();
}


void timer1(int value) {
	if (value == 0)
		return;

	timer_cnt++;
	timer_cnt %= 100;
	
	glutPostRedisplay();
	glutTimerFunc(10, timer1, 1);
}

void initGL() {
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glDisable(GL_LIGHTING);
	glEnable(GL_DEPTH_TEST);

	// camera setting
	{
		GLfloat aspectRatio = (GLfloat)WIDTH / (GLfloat)HEIGHT;

		glViewport(0, 0, WIDTH, HEIGHT);

		// projection matrix
		projection = glm::perspective(glm::radians(45.0f), aspectRatio, 0.1f, 100.0f);
		glLoadMatrixf(glm::value_ptr(projection));

		// View
		view = glm::lookAt(
			glm::vec3(0.0f, 0.0f, 5.0f),
			glm::vec3(0.0f, 0.0f, 0.0f),
			glm::vec3(0.0f, 1.0f, 0.0f)
		);
	}

	// others setting
	timer_cnt = 0;
	star = new Star();

}


int main(int argc, char * argv[]) {
	glutInit(&argc, argv);

	// create window
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(WIDTH, HEIGHT);
	glutCreateWindow("CG_Q1");

	// glew initiatlize
	glewExperimental = GL_TRUE;
	if (glewInit() == -1) {
		std::cout << "glewInit() error!" << std::endl;
		return 0;
	}


	// setting callback functions.
	glutReshapeFunc(reshape);
	glutMouseFunc(mouse);
	glutMotionFunc(mouseMotion);
	glutDisplayFunc(display);
	glutTimerFunc(10, timer1, 1);

	initGL();

	glutMainLoop();
}