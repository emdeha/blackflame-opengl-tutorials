#ifndef MATRIXSTACK_H
#define MATRIXSTACK_H

#include <stack>
#include <glm/glm.hpp>

class MatrixStack
{
private:
	glm::mat4 currentMatrix;
	std::stack<glm::mat4> matrices;

public:
	MatrixStack()
	{
		currentMatrix = glm::mat4(1.0f);
	}

	glm::mat4 &Top();

	void Push();
	void Pop();

	void RotateX(float angle_degs);
	void RotateY(float angle_degs);
	void RotateZ(float angle_degs);

	void Scale(const glm::vec3 &scaleVector);

	void Translate(const glm::vec3 &offsetVector);
};

#endif