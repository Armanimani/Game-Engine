#include "OrthoFreeCamera.h"
#include <iostream>

void OrthoFreeCamera::moveForward(const GLfloat & value)
{
	if ((frustum.viewLeft + scale + value * aspectRatio) > (frustum.viewRight - scale - value * aspectRatio) || ((frustum.viewBottom + scale + value) > (frustum.viewTop - scale - value))) return;
	scale += value;
}

void OrthoFreeCamera::updateProjectionMatrix()
{
	projectionMatrix = glm::ortho(frustum.viewLeft + scale * aspectRatio, frustum.viewRight - scale * aspectRatio, frustum.viewBottom + scale, frustum.viewTop - scale, frustum.viewBack, frustum.viewFront);
}
