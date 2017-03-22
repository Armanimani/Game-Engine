#include "FPSCamera.h"
#include <iostream>

const GLfloat MAX = 89.99f;
const GLfloat MIN = -89.99f;

void FPSCamera::rotateRight(const GLfloat & value)
{
	GLfloat v = value;
	if (theta + value >= MAX) v = MAX - theta;
	else if (theta + value <= MIN) v = MIN - theta;
	else v = value;

	theta += v;
	FreeCamera::rotateRight(v);
}