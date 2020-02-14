#ifndef LSHAPE_H
#define LSHAPE_H

#include <iostream>
#include "Angel.h"
#include <Math.h>

using namespace Angel;

typedef vec4 color4;
typedef vec4 point4;

const int NumVertices = 12;
const double PI = 3.141592653589793238463;

GLint theta;

const GLint width = 500;
const GLint height = 500;

const GLint n = 8; // number of rotations

GLfloat referenceX = 0.125; // x coordinates of reference point of LShape
GLfloat referenceY = 0; // y coordinates of reference point of LShape

/* int positions for locations of uniform variables */
GLint uniformTranslateToOriginPos;
GLint uniformTranslateToMousePos;
GLint uniformTranslateForAnimatePos;

GLint thetaPosition; // for rotation degree

point4 points[NumVertices]; // holds vertices of LShape
color4 colors[NumVertices]; // holds color of vertices of LShape

/* vectors for translations */
vec3 translateToOrigin = { 0.0,0.0,0.0 };
vec3 translateToMouse = { 0.0,0.0,0.0 };
vec3 translateForAnimate = { 0.0,0.0,0.0 };

/* enum for mode of program */
enum modes { SINGLE_ROTATION_MODE, ANIMATION_MODE };

int mode;

//Initial positions of vertices of LShape

/* vertices of LShape
	1---2
	 - -
	 - -
	 - -3
	 -------------4
	0-------------5
*/

point4 LShape[6] = {
	point4(0.0,0.0 ,0.0, 1.0),
	point4(0.0,0.35 ,0.0, 1.0),
	point4(0.1,0.35 ,0.0, 1.0),
	point4(0.1,0.1 ,0.0, 1.0),
	point4(0.25,0.1 ,0.0, 1.0),
	point4(0.25,0.0 ,0.0, 1.0),
};

color4 color = { 0.5,0.5,0.5,1.0 };

/* function prototypes */
void quad(int a, int b, int c, int d);
void fillPointsAndColors();
void init();
void myDisplay(void);
void singleRotationMode(int x, int y);
void myMouse(int btn, int state, int x, int y);
void animate(int id);
void myKeyboard(unsigned char key, int x, int y);

#endif