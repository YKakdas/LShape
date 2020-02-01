#include <iostream>
#include "Angel.h"
#include <Math.h>

using namespace Angel;

typedef vec4 color4;
typedef vec4 point4;

const int NumVertices = 12;
const double PI = 3.141592653589793238463;
mat4 translate;

GLint theta = 5;

GLint width = 500;
GLint height = 500;
point4 points[NumVertices];
color4 colors[NumVertices];
point4 transformedPoints[NumVertices];


point4 LShape[6] = {
	point4(-1.0,-1.0 ,0.0, 1.0),
	point4(-1.0,-0.65 ,0.0, 1.0),
	point4(-0.9,-0.65 ,0.0, 1.0),
	point4(-0.9,-0.9 ,0.0, 1.0),
	point4(-0.75,-0.9 ,0.0, 1.0),
	point4(-0.75,-1.0 ,0.0, 1.0),
};


// RGBA colors
color4 vertex_colors[6] = {
	color4(0.0, 0.0, 0.0, 1.0),  // black
	color4(1.0, 0.0, 0.0, 1.0),  // red
	color4(1.0, 1.0, 0.0, 1.0),  // yellow
	color4(0.0, 1.0, 0.0, 1.0),  // green
	color4(0.0, 0.0, 1.0, 1.0),  // blue
	color4(0.0, 1.0, 1.0, 1.0)  // magenta
};

int Index = 0;

void quad(int a, int b, int c, int d)
{
	colors[Index] = vertex_colors[a]; points[Index] = LShape[a]; Index++;
	colors[Index] = vertex_colors[b]; points[Index] = LShape[b]; Index++;
	colors[Index] = vertex_colors[c]; points[Index] = LShape[c]; Index++;
	colors[Index] = vertex_colors[a]; points[Index] = LShape[a]; Index++;
	colors[Index] = vertex_colors[c]; points[Index] = LShape[c]; Index++;
	colors[Index] = vertex_colors[d]; points[Index] = LShape[d]; Index++;
}

void fillPointsAndColors()
{
	quad(0, 1, 2, 3);
	quad(3, 4, 5, 0);
}

void init()
{
	//fillPointsAndColors();
	fillPointsAndColors();
	// Create a vertex array object
	GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	// Create and initialize a buffer object
	GLuint buffer;
	glGenBuffers(1, &buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(points) + sizeof(colors),
		NULL, GL_DYNAMIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(points), points);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(points), sizeof(colors), colors);

	// Load shaders and use the resulting shader program
	GLuint program = InitShader("vshader.glsl", "fshader.glsl");
	glUseProgram(program);

	// set up vertex arrays
	GLuint vPosition = glGetAttribLocation(program, "vPosition");
	glEnableVertexAttribArray(vPosition);
	glVertexAttribPointer(vPosition, 4, GL_FLOAT, GL_FALSE, 0,
		BUFFER_OFFSET(0));

	GLuint vColor = glGetAttribLocation(program, "vColor");
	glEnableVertexAttribArray(vColor);
	glVertexAttribPointer(vColor, 4, GL_FLOAT, GL_FALSE, 0,
		BUFFER_OFFSET(sizeof(points)));

	glEnable(GL_DEPTH_TEST);
	glClearColor(1.0, 1.0, 1.0, 1.0);
	translate = identity();
	translate[0][3] = 0.875;
	translate[1][3] = 1.4;
	
	for (int i = 0; i < NumVertices; i++) {
		points[i] = translate * points[i];
	}
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(points), points);
}
void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	glDrawArrays(GL_TRIANGLES, 0, NumVertices);

	glutSwapBuffers();
}

void myMouse(int btn, int state, int x, int y) {
	if (btn == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
		
		GLfloat newX = (GLfloat)x / 250.0 - 0.125;
		translate = identity();
		translate[0][3] = newX;
		translate[1][3] = (GLfloat)(500-y)/250.0;
	
		
		for (int i = 0; i < NumVertices; i++) {
			points[i] = translate * points[i];
		}
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(points), points);
		glutPostRedisplay();

	}
	if (btn == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {

		GLfloat x = (points[0].x + points[10].x) / 2;
		GLfloat y = (points[0].y);

		translate[0][3] = -x;
		translate[1][3] = -y;
		
		GLfloat angle = 2 * PI * 30 / 360;

		mat4 rotate = identity();
		rotate[0][0] = cos(angle);
		rotate[0][1] = -sin(angle);
		rotate[1][0] = sin(angle);
		rotate[1][1] = cos(angle);

		mat4 translateBack = identity();
		translateBack[0][3] = x;
		translateBack[1][3] = y;

		mat4 totalMatrix = translateBack *rotate*translate;
		
		for (int i = 0; i < NumVertices; i++) {
			points[i] = totalMatrix * points[i];
		}
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(points), points);
		theta += 5;
		glutPostRedisplay();
	}
}

void changeAngle(int id) {
	theta += 30;

	GLfloat angle = 2 * PI * theta / 360;
	mat4 rotate = identity();
	rotate[0][0] = cos(angle);
	rotate[0][1] = -sin(angle);
	rotate[1][0] = sin(angle);
	rotate[1][1] = cos(angle);

	point4 tempPoints[NumVertices];
	for (int i = 0; i < NumVertices; i++) {
		tempPoints[i] = rotate * points[i];
	}
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(tempPoints), tempPoints);
	glutPostRedisplay();
	glutTimerFunc(500, changeAngle, 0);
}
int main(int argc, char **argv)
{
	glutInit(&argc, argv);


	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(width, height);

	glutCreateWindow("Color Cube");
	glewExperimental = GL_TRUE;
	glewInit();

	init();

	glutTimerFunc(500, changeAngle, 0);
	glutMouseFunc(myMouse);
	glutDisplayFunc(display);
	glutMainLoop();
	return 0;
}
