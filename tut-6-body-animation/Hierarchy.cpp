#include "Hierarchy.h"
#include "MatrixOperations.h"

Node::Node()
{
	position = glm::vec3();
	axisPosition = glm::vec3();
	scale = glm::vec3();

	angleX_degs = 0.0f;
	angleY_degs = 0.0f;
	angleZ_degs = 0.0f;

	animAngleMinX_degs = 0.0f;
	animAngleMaxX_degs = 0.0f;
	animAngleMinY_degs = 0.0f;
	animAngleMaxY_degs = 0.0f;
	animAngleMinZ_degs = 0.0f;
	animAngleMaxZ_degs = 0.0f;

	decrement = 1.0f;

	childNodes.resize(0);
	
	parent = NULL;
}

Node::Node(glm::vec3 newPosition, glm::vec3 newAxisPosition, glm::vec3 newScale, 
		   float newAngleX_degs, float newAngleY_degs, float newAngleZ_degs,
		   float newAnimAngleMinX_degs, float newAnimAngleMaxX_degs,
		   float newAnimAngleMinY_degs, float newAnimAngleMaxY_degs,
		   float newAnimAngleMinZ_degs, float newAnimAngleMaxZ_degs,
		   float newDecrement)
{
	position = newPosition;
	axisPosition = newAxisPosition;
	scale = newScale;
	
	angleX_degs = newAngleX_degs;
	angleY_degs = newAngleY_degs;
	angleZ_degs = newAngleZ_degs;

	animAngleMinX_degs = newAnimAngleMinX_degs;
	animAngleMaxX_degs = newAnimAngleMaxX_degs;
	animAngleMinY_degs = newAnimAngleMinY_degs;
	animAngleMaxY_degs = newAnimAngleMaxY_degs;
	animAngleMinZ_degs = newAnimAngleMinZ_degs;
	animAngleMaxZ_degs = newAnimAngleMaxZ_degs;

	decrement = newDecrement;

	childNodes.resize(0);
	
	parent = NULL;
}

void Node::RenderWithoutMatrixStack(Node *node, glm::mat4 &matrix, GLuint matrixUnif)
{
	if(node->parent != NULL)
	{
		matrix *= Transform::Translate(node->position);

		matrix *= Transform::RotateZ(node->angleZ_degs);
		matrix *= Transform::RotateY(node->angleY_degs);
		matrix *= Transform::RotateX(node->angleX_degs);
	}

	{
		glm::mat4 subMat(1.0f);
		subMat *= matrix;
		subMat *= Transform::Translate(node->axisPosition);
		subMat *= Transform::Scale(node->scale);
		glUniformMatrix4fv(matrixUnif, 1, GL_FALSE, glm::value_ptr(subMat));
		glDrawElements(GL_TRIANGLES, ARRAY_COUNT(indexDataH), GL_UNSIGNED_SHORT, 0);
	}

	int size = node->childNodes.size();
	for(int i = 0; i < size; i++)
	{
		glm::mat4 childMat(1.0f);
		childMat *= matrix;
		Node::RenderWithoutMatrixStack(node->childNodes[i], childMat, matrixUnif);
	}
}

void Node::Render(Node *node, MatrixStack &stack, GLuint matrixUnif)
{
	if(node->parent != NULL)
	{
		stack.Translate(node->position);	
			
		stack.RotateZ(node->angleZ_degs);
		stack.RotateY(node->angleY_degs);
		stack.RotateX(node->angleX_degs);
	}

	{
		stack.Push();

			stack.Translate(node->axisPosition);
			stack.RotateZ(node->angleZ_degs);
			stack.RotateY(node->angleY_degs);
			stack.RotateX(node->angleX_degs);
			stack.Scale(node->scale);
			glUniformMatrix4fv(matrixUnif, 1, GL_FALSE, glm::value_ptr(stack.Top()));
			glDrawElements(GL_TRIANGLES, ARRAY_COUNT(indexDataH), GL_UNSIGNED_SHORT, 0);

		stack.Pop();
	}

	int size = node->childNodes.size();
	for(int i = 0; i < size; i++)
	{
		stack.Push();
			Node::Render(node->childNodes[i], stack, matrixUnif);
		stack.Pop();
	}
}

#define STANDARD_ANGLE_INCREMENT 1.0f
#define SMALL_ANGLE_INCREMENT 9.0f

inline float Clamp(float fValue, float fMinValue, float fMaxValue)
{
	if(fValue < fMinValue)
		return fMinValue;

	if(fValue > fMaxValue)
		return fMaxValue;

	return fValue;
}

void Node::AdjustAngX(bool increment, float minVal, float maxVal)
{
	angleX_degs += increment ? STANDARD_ANGLE_INCREMENT : -STANDARD_ANGLE_INCREMENT;
	if(minVal != maxVal)
		angleX_degs = Clamp(angleX_degs, minVal, maxVal);
}
void Node::AdjustAngY(bool increment, float minVal, float maxVal)
{
	angleY_degs += increment ? STANDARD_ANGLE_INCREMENT : -STANDARD_ANGLE_INCREMENT;
	if(minVal != maxVal)
		angleY_degs = Clamp(angleY_degs, minVal, maxVal);
}
void Node::AdjustAngZ(bool increment, float minVal, float maxVal)
{
	angleZ_degs += increment ? STANDARD_ANGLE_INCREMENT : -STANDARD_ANGLE_INCREMENT;
	if(minVal != maxVal)
		angleZ_degs = Clamp(angleZ_degs, minVal, maxVal);
}

void Node::AdjustAnimAngleX()
{
	if(animAngleMinX_degs != animAngleMaxX_degs)
	{
		if(angleX_degs == animAngleMinX_degs)
		{
			decrement *= -1.0f;
		}
		if(angleX_degs == animAngleMaxX_degs)
		{
			decrement *= -1.0f;
		}
		angleX_degs += decrement;

		angleX_degs = Clamp(angleX_degs, animAngleMinX_degs, animAngleMaxX_degs);
	}
}
void Node::AdjustAnimAngleY()
{	
	if(animAngleMinY_degs != animAngleMaxY_degs)
	{
		if(angleY_degs == animAngleMinY_degs)
		{
			decrement *= -1.0f;
		}
		if(angleY_degs == animAngleMaxY_degs)
		{
			decrement *= -1.0f;
		}
		angleY_degs += decrement;

		angleY_degs = Clamp(angleY_degs, animAngleMinY_degs, animAngleMaxY_degs);
	}
}
void Node::AdjustAnimAngleZ()
{
	if(animAngleMinZ_degs != animAngleMaxZ_degs)
	{
		if(angleZ_degs == animAngleMinZ_degs)
		{
			decrement *= -1.0f;
		}
		if(angleZ_degs == animAngleMaxZ_degs)
		{
			decrement *= -1.0f;
		}
		angleZ_degs += decrement;

			angleZ_degs = Clamp(angleZ_degs, animAngleMinZ_degs, animAngleMaxZ_degs);
	}
}

void Node::Update(Node *node)
{
	if(node->parent != NULL)
	{
		node->AdjustAnimAngleX();
		node->AdjustAnimAngleY();
		node->AdjustAnimAngleZ();
	}

	int size = node->childNodes.size();
	for(int i = 0; i < size; i++)
	{
		Node::Update(node->childNodes[i]);
	}
}

void Node::AddChild(Node *child)
{
	childNodes.push_back(child);
	child->parent = this;
}

////////////////////////
//---Root node code---//
////////////////////////

RootNode::RootNode()
{
	position = glm::vec3();

	angleX_degs = 0.0f;
	angleY_degs = 0.0f;
	angleZ_degs = 0.0f;

	childNodes.resize(0);
}
RootNode::RootNode(glm::vec3 newPosition,
				   float newAngleX_degs, float newAngleY_degs, float newAngleZ_degs)
{
	position = newPosition;

	angleX_degs = newAngleX_degs;
	angleY_degs = newAngleY_degs;
	angleZ_degs = newAngleZ_degs;

	childNodes.resize(0);
}

void RootNode::RenderWithoutMatrixStack(GLuint shaderProgram, GLuint vao, GLuint matrixUnif)
{
	glUseProgram(shaderProgram);
	glBindVertexArray(vao);

	glm::mat4 matrix;

	matrix *= Transform::Translate(position);
	matrix *= Transform::RotateX(angleX_degs);
	matrix *= Transform::RotateY(angleY_degs);
	matrix *= Transform::RotateZ(angleZ_degs);

	int size = childNodes.size();
	for(int i = 0; i < size; i++)
	{
		Node::RenderWithoutMatrixStack(childNodes[i], matrix, matrixUnif);
	}

	glBindVertexArray(0);
	glUseProgram(0);
}

void RootNode::Render(GLuint shaderProgram, GLuint vao, GLuint matrixUnif)
{
	MatrixStack modelToCameraStack;

	glUseProgram(shaderProgram);
	glBindVertexArray(vao);

	modelToCameraStack.Translate(position);
	modelToCameraStack.RotateX(angleX_degs);
	modelToCameraStack.RotateY(angleY_degs);
	modelToCameraStack.RotateZ(angleZ_degs);

	int size = childNodes.size();
	for(int i = 0; i < size; i++)
	{
		Node::Render(childNodes[i], modelToCameraStack, matrixUnif);
	}

	glBindVertexArray(0);
	glUseProgram(0);
}

void RootNode::Update()
{
	int size = childNodes.size();
	for(int i = 0; i < size; i++)
	{
		//Node::Update(childNodes[i]);
	}
}

void RootNode::AdjustAngX(bool increment, float minVal, float maxVal)
{
	angleX_degs += increment ? STANDARD_ANGLE_INCREMENT : -STANDARD_ANGLE_INCREMENT;
	if(minVal != maxVal)
		angleX_degs = Clamp(angleX_degs, minVal, maxVal);
}
void RootNode::AdjustAngY(bool increment, float minVal, float maxVal)
{
	angleY_degs += increment ? STANDARD_ANGLE_INCREMENT : -STANDARD_ANGLE_INCREMENT;
	if(minVal != maxVal)	
		angleY_degs = Clamp(angleY_degs, minVal, maxVal);
}
void RootNode::AdjustAngZ(bool increment, float minVal, float maxVal)
{
	angleZ_degs += increment ? STANDARD_ANGLE_INCREMENT : -STANDARD_ANGLE_INCREMENT;
	if(minVal != maxVal)
		angleZ_degs = Clamp(angleZ_degs, minVal, maxVal);
}


void RootNode::AddChild(Node *child)
{
	childNodes.push_back(child);
}