#include <iostream>
#include "Angel.h"

using namespace Angel;

typedef vec4 color4;
typedef vec4 point4;

const int NumVertices = 12;


GLint width = 500;
GLint height = 500;
point4 points[NumVertices];
color4 colors[NumVertices];

point4 vertices[6] = {
	point4(0.0 , 0.0 , 0.0 , 1.0),
	point4(0.0 , 80.0 , 0.0 , 1.0),
	point4(20.0 , 80.0 , 0.0 , 1.0),
	point4(20.0 , 20.0 , 0.0 , 1.0),
	point4(60.0 , 20.0 , 0.0 , 1.0),
	point4(60.0 , 0.0 , 0.0, 1.0)
};

// RGBA colors
color4 vertex_colors[6] = {
	color4(0.5, 0.5, 0.5, 1.0),  // black
	color4(0.5, 0.5, 0.5, 1.0),  // red
	color4(0.5, 0.5, 0.5, 1.0),  // yellow
	color4(0.5, 0.5, 0.5, 1.0),  // green
	color4(0.5, 0.5, 0.5, 1.0),  // blue
	color4(0.5, 0.5, 0.5, 1.0)  // magenta
};

int Index = 0;

void quad(int a, int b, int c, int d)
{
	colors[Index] = vertex_colors[a]; points[Index] = vertices[a]; Index++;
	colors[Index] = vertex_colors[b]; points[Index] = vertices[b]; Index++;
	colors[Index] = vertex_colors[c]; points[Index] = vertices[c]; Index++;
	colors[Index] = vertex_colors[a]; points[Index] = vertices[a]; Index++;
	colors[Index] = vertex_colors[c]; points[Index] = vertices[c]; Index++;
	colors[Index] = vertex_colors[d]; points[Index] = vertices[d]; Index++;
}

void normalizeVector(vec4 * vector) {
	vector->x = (vector->x - 250) / 250;
	vector->y = (vector->y - 250) / 250;
	vector->z = (vector->z - 250) / 250;
}

void fillPointsAndColors()
{
	for (int i = 0; i < NumVertices / 2; i++) {
		normalizeVector(&vertices[i]);
	}
	quad(0, 1, 2, 3);
	quad(3, 4, 5, 0);
}



void init()
{
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
		NULL, GL_STATIC_DRAW);
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
}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//	mat4 translate = identity();
	//	translate[0][3] = 0.5;
	//	for (int i = 0; i <NumVertices; i++) {
	//		points[i] = translate * points[i];
	//	}
	//	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(points), points);

	glDrawArrays(GL_TRIANGLES, 0, NumVertices);

	glutSwapBuffers();
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

	glutDisplayFunc(display);
	glutMainLoop();
	return 0;
}
