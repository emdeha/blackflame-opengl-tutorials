#include "SceneObjects.h"

#include <glm/gtc/type_ptr.hpp>

#define ARRAY_COUNT( array ) (sizeof( array ) / (sizeof( array[0] ) * (sizeof( array ) != sizeof(void*) || sizeof( array[0] ) <= sizeof(void*))))

Paddle::Paddle(float zPosition)
{
	position = glm::vec3(0.0f, 0.0f, zPosition);
	minCorner = glm::vec3(-1.0f, -1.0f, zPosition);
	maxCorner = glm::vec3(1.0f, 1.0f, zPosition);

	offsetX = 0.0f;
	offsetY = 0.0f;
	prevOffsetX = 0.0f;
	prevOffsetY = 0.0f;

	isLockedAndLoaded = false;
	isAI = false;
	isMiss = false;
}

void Paddle::MoveX(float delta)
{
	prevOffsetX = offsetX;
	offsetX += delta;

	if(offsetX > 0.88f)
	{
		offsetX = 0.88f;
	}
	else if(offsetX < -0.88f)
	{
		offsetX = -0.88f;
	}

	position.x = offsetX;
}

void Paddle::MoveY(float delta)
{
	prevOffsetY = offsetY;
	offsetY += delta;

	if(offsetY > 0.5f)
	{
		offsetY = 0.5f;
	}
	else if(offsetY < -0.5f)
	{
		offsetY = -0.5f;
	}

	position.y = offsetY;
}

void Paddle::Render(glm::mat4 &transform, 
					GLuint shaderProgram, GLuint vao, 
					GLuint matrixUnif)
{
	glUseProgram(shaderProgram);
	glBindVertexArray(vao);

	transform *= Transform::Translate(glm::vec3(position));
	transform *= Transform::Scale(glm::vec3(0.1f, 0.1f, 0.1f));

	glUniformMatrix4fv(matrixUnif, 1, GL_FALSE, glm::value_ptr(transform));
	glDrawElements(GL_TRIANGLES, ARRAY_COUNT(indexDataPaddleH), GL_UNSIGNED_SHORT, 0);

	glBindVertexArray(0);
	glUseProgram(0);
}

void Paddle::Update(glm::vec3 ballPosition)
{
	if(isAI)
	{
		if(ballPosition.x >= maxCorner.x*0.1f + offsetX)
		{
			MoveX(0.04f);
		}
		else if(ballPosition.x <= minCorner.x*0.1f + offsetX)
		{
			MoveX(-0.04f);
		}
		else if(ballPosition.y >= maxCorner.y*0.1f + offsetY)
		{
			MoveY(0.04f);
		}
		else if(ballPosition.y <= minCorner.y*0.1f + offsetY)
		{
			MoveY(-0.04f);
		}
		else
		{
			prevOffsetX = offsetX;
			prevOffsetY = offsetY;
		}
	}
}

glm::vec3 Paddle::GetPosition()
{
	return position;
}
glm::vec3 Paddle::GetMaxCorner()
{
	return maxCorner;
}
glm::vec3 Paddle::GetMinCorner()
{
	return minCorner;
}
float Paddle::GetDifferenceX()
{
	return prevOffsetX - offsetX;
}
float Paddle::GetDifferenceY()
{
	return prevOffsetY - offsetY;
}
float Paddle::GetOffsetX()
{
	return offsetX;
}
float Paddle::GetOffsetY()
{
	return offsetY;
}
bool Paddle::IsLockedAndLoaded()
{
	return isLockedAndLoaded;
}
bool Paddle::IsMiss()
{
	return isMiss;
}

void Paddle::LockAndLoad()
{
	isLockedAndLoaded = true;
}
void Paddle::UnLockAndLoad()
{
	isLockedAndLoaded = false;
}
void Paddle::SetAI(bool newIsAI)
{
	isAI = newIsAI;
}
void Paddle::SetMiss(bool newIsMiss)
{
	isMiss = newIsMiss;
}

//------------//
// Ball class //
//------------//
BoxBall::BoxBall(glm::vec3 newVelocity)
{
	position = glm::vec3(0.0f, 0.0f, -3.9f);

	velocity = newVelocity;
}

void BoxBall::Render(glm::mat4 &transform,
					 GLuint shaderProgram, GLuint vao,
					 GLuint matrixUnif)
{
	glUseProgram(shaderProgram);
	glBindVertexArray(vao);

	transform *= Transform::Translate(glm::vec3(position));
	transform *= Transform::Scale(glm::vec3(0.05f, 0.05f, 0.05f));

	glUniformMatrix4fv(matrixUnif, 1, GL_FALSE, glm::value_ptr(transform));
	glDrawElements(GL_TRIANGLES, ARRAY_COUNT(indexDataBallH), GL_UNSIGNED_SHORT, 0);

	glBindVertexArray(0);
	glUseProgram(0);
}

void BoxBall::Update(Paddle &pad, bool isFirst)
{
	if(pad.IsLockedAndLoaded())
	{
		position = position + velocity;
		CheckCollision(pad, isFirst);
	}
	// TODO: When game starts, place the ball on the pad.
	if(pad.IsMiss())
	{
		velocity = glm::vec3(0.0f, 0.0f, -0.05f);
		position = glm::vec3(0.0f, 0.0f, -1.95f);
	}
}

glm::vec3 BoxBall::GetPosition()
{
	return position;
}

void BoxBall::CheckWallCollision(Paddle &pad)
{
	if(position.x > 0.93f)
	{
		velocity.x *= -1;
	}
	else if(position.x < -0.93f)
	{
		velocity.x *= -1;
	}

	if(position.y > 0.55f)
	{
		velocity.y *= -1;
	}
	else if(position.y < -0.55f)
	{
		velocity.y *= -1;
	}

	if(position.z < -5.8f)
	{
		pad.SetMiss(true);
		position = glm::vec3();
		position.z = -5.65f;
	}
	else if(position.z > -1.8f)
	{
		pad.SetMiss(true);
		position = glm::vec3();
		position.z = -1.95f;
	}
}

bool BoxBall::IsInPaddle(Paddle &pad)
{
	if(position.x + 0.05f > pad.GetMinCorner().x*0.1f + pad.GetOffsetX() &&
	   position.y + 0.05f > pad.GetMinCorner().y*0.1f + pad.GetOffsetY() &&
	   position.x + 0.05f < pad.GetMaxCorner().x*0.1f + pad.GetOffsetX() &&
	   position.y + 0.05f < pad.GetMaxCorner().y*0.1f + pad.GetOffsetY())
	{
		return true;
	}
	if(position.x - 0.05f > pad.GetMinCorner().x*0.1f + pad.GetOffsetX() &&
	   position.y - 0.05f > pad.GetMinCorner().y*0.1f + pad.GetOffsetY() &&
	   position.x - 0.05f < pad.GetMaxCorner().x*0.1f + pad.GetOffsetX() &&
	   position.y - 0.05f < pad.GetMaxCorner().y*0.1f + pad.GetOffsetY())
	{
		return true;
	}
	if(position.x - 0.05f > pad.GetMinCorner().x*0.1f + pad.GetOffsetX() &&
	   position.y + 0.05f > pad.GetMinCorner().y*0.1f + pad.GetOffsetY() &&
	   position.x - 0.05f < pad.GetMaxCorner().x*0.1f + pad.GetOffsetX() &&
	   position.y + 0.05f < pad.GetMaxCorner().y*0.1f + pad.GetOffsetY())
	{
		return true;
	}
	if(position.x + 0.05f > pad.GetMinCorner().x*0.1f + pad.GetOffsetX() &&
	   position.y - 0.05f > pad.GetMinCorner().y*0.1f + pad.GetOffsetY() &&
	   position.x + 0.05f < pad.GetMaxCorner().x*0.1f + pad.GetOffsetX() &&
	   position.y - 0.05f < pad.GetMaxCorner().y*0.1f + pad.GetOffsetY())
	{
		return true;
	}
	
	return false;
}

void BoxBall::CheckPaddleCollision(Paddle &pad, bool isFirst)
{
	if(!isFirst)
	{
		if(IsInPaddle(pad) && position.z <= -5.65f)
		{
			velocity.x += 0.05f * pad.GetDifferenceX();
			velocity.y += 0.05f * pad.GetDifferenceY();
			velocity.z *= -1;
		}
	}
	if(isFirst)
	{
		if(IsInPaddle(pad) && position.z >= -1.95f)
		{
			velocity.x += 0.05f * pad.GetDifferenceX();
			velocity.y += 0.05f * pad.GetDifferenceY();
			velocity.z *= -1;
		}
	}
}

void BoxBall::CheckCollision(Paddle &pad, bool isFirst)
{
	CheckPaddleCollision(pad, isFirst);
	CheckWallCollision(pad);
}



//----------------//
// Boundary class //
//----------------//
void Boundary::Render(glm::mat4 &transform, 
					  GLuint shaderProgram, GLuint vao,
				      GLuint matrixUnif)
{
	glUseProgram(shaderProgram);
	glBindVertexArray(vao);

	transform *= Transform::Translate(glm::vec3(0.0f, 0.0f, -4.0f));
	transform *= Transform::Scale(glm::vec3(1.032f, 0.631f, 2.0f));
	transform *= Transform::RotateY(90.0f);
	
	glUniformMatrix4fv(matrixUnif, 1, GL_FALSE, glm::value_ptr(transform));
	glDrawElements(GL_TRIANGLES, ARRAY_COUNT(indexDataBoundH), GL_UNSIGNED_SHORT, 0);

	glBindVertexArray(0);
	glUseProgram(0);
}