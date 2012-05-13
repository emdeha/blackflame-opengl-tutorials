#ifndef MATRIX_OPERATIONS_H
#define MATRIX_OPERATIONS_H

#pragma once

#include <glm/glm.hpp>

namespace Transform
{
	inline float DegToRad(float angle_degs);

	glm::mat4 RotateX(float angle_degs);
	glm::mat4 RotateY(float angle_degs);
	glm::mat4 RotateZ(float angle_degs);

	glm::mat4 Scale(const glm::vec3 &scaleVector);

	glm::mat4 Translate(const glm::vec3 &offsetVector);
}

#endif