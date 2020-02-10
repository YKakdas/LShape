#include "LShape.h"

/* vertices of LShape
	1---2
	 - -
	 - -
	 - -3
	 -------------4
	0-------------5
*/

int index = 0;

void quad(int a, int b, int c, int d) {
	colors[index] = color; points[index] = LShape[a]; index++;
	colors[index] = color; points[index] = LShape[b]; index++;
	colors[index] = color; points[index] = LShape[c]; index++;
	colors[index] = color; points[index] = LShape[a]; index++;
	colors[index] = color; points[index] = LShape[c]; index++;
	colors[index] = color; points[index] = LShape[d]; index++;
}

void fillPointsAndColors() { // to fill points array and colors array for LShape vertices
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

	uniformTranslateToOriginPos = glGetUniformLocation(program, "translateToOrigin");
	uniformTranslateToMousePos = glGetUniformLocation(program, "translateToMouse");
	uniformTranslateForAnimatePos = glGetUniformLocation(program, "translateForAnimate");
	thetaPosition = glGetUniformLocation(program, "theta");

	GLuint vColor = glGetAttribLocation(program, "vColor");
	glEnableVertexAttribArray(vColor);
	glVertexAttribPointer(vColor, 4, GL_FLOAT, GL_FALSE, 0,
		BUFFER_OFFSET(sizeof(points)));

	glEnable(GL_DEPTH_TEST);
	glClearColor(1.0, 1.0, 1.0, 1.0);
}
void myDisplay(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glUniform1f(thetaPosition, theta);
	glUniform3fv(uniformTranslateToOriginPos, 1, translateToOrigin);
	glUniform3fv(uniformTranslateToMousePos, 1, translateToMouse);
	glUniform3fv(uniformTranslateForAnimatePos, 1, translateForAnimate);

	glDrawArrays(GL_TRIANGLES, 0, NumVertices);

	glutSwapBuffers();
}

void singleRotationMode(int x, int y) {
	translateForAnimate = { 0.0,0.0,0.0 };
	translateToOrigin.x = -referenceX;
	translateToOrigin.y = -referenceY;
	translateToOrigin.z = 0.0;
	theta = 30;
	translateToMouse.x = (GLfloat)x / 250.0 - 1;
	translateToMouse.y = (GLfloat)y / 250.0 - 1;
	translateToMouse.z = 0.0;

	glutPostRedisplay();
}
void myMouse(int btn, int state, int x, int y) {
	if (btn == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
		singleRotationMode(x, height - y);
		mode = SINGLE_ROTATION_MODE;
	}
}

void animate(int id) {
	if (mode != ANIMATION_MODE) {
		theta = 0;
		return;
	}

	if (id == 0) {
		theta = 0;
	}
	else {
		theta += 360 / n;
	}
	
	translateToOrigin.x = -referenceX;
	translateToOrigin.y = -referenceY;
	translateToOrigin.z = 0.0;

	translateForAnimate.x = -sin(theta * 2 * PI / 360) * 100 / 250;
	translateForAnimate.y = cos(theta * 2 * PI / 360) * 100 / 250;
	translateForAnimate.z = 0.0;

	translateToMouse = { 0.0,0.0,0.0 };

	glutPostRedisplay();
	glutTimerFunc(1000, animate, 1);
}
void myKeyboard(unsigned char key, int x, int y) {
	if (key == 'r' || key == 'R') {
		if (mode == SINGLE_ROTATION_MODE) {
			theta += 5;
			glutPostRedisplay();
		}
	}
	else if (key == 'a' || key == 'A') {
		mode = ANIMATION_MODE;
		glutTimerFunc(1000, animate, 0);
	}
}

int main(int argc, char **argv) {
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(width, height);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("LShape");
	glewExperimental = GL_TRUE;
	glewInit();

	init();

	glutKeyboardFunc(myKeyboard);
	glutMouseFunc(myMouse);
	glutDisplayFunc(myDisplay);
	glutMainLoop();
	return 0;
}