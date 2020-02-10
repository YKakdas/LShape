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

const GLint n = 8;

GLfloat referenceX = 0.125;
GLfloat referenceY = 0;

GLint uniformTranslateToOriginPos;
GLint uniformTranslateToMousePos;
GLint uniformTranslateForAnimatePos;

GLint thetaPosition;

point4 points[NumVertices];
color4 colors[NumVertices];

vec3 translateToOrigin = { 0.0,0.0,0.0 };
vec3 translateToMouse = { 0.0,0.0,0.0 };
vec3 translateForAnimate = { 0.0,0.0,0.0 };

enum modes { SINGLE_ROTATION_MODE, ANIMATION_MODE };

int mode;


point4 LShape[6] = {
	point4(0.0,0.0 ,0.0, 1.0),
	point4(0.0,0.35 ,0.0, 1.0),
	point4(0.1,0.35 ,0.0, 1.0),
	point4(0.1,0.1 ,0.0, 1.0),
	point4(0.25,0.1 ,0.0, 1.0),
	point4(0.25,0.0 ,0.0, 1.0),
};

color4 color = { 0.5,0.5,0.5,1.0 };

void quad(int a, int b, int c, int d);
void fillPointsAndColors();
void init();
void myDisplay(void);
void singleRotationMode(int x, int y);
void myMouse(int btn, int state, int x, int y);
void animate(int id);
void myKeyboard(unsigned char key, int x, int y);

#endif