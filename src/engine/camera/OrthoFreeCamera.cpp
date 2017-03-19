#include "OrthoFreeCamera.h"

void OrthoFreeCamera::updateProjectionMatrix()
{
	projectionMatrix = glm::ortho(frustum.viewLeft, frustum.viewRight, frustum.viewBottom, frustum.viewTop, frustum.viewBack, frustum.viewFront);
}
