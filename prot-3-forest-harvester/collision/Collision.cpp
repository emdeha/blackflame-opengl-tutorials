#include "stdafx.h"
#include "Collision.h"
#include <iostream>
#include <math.h>
#include <assert.h>


static float VectorLength(glm::vec3 vect)
{
	float x = vect.x * vect.x;
	float y = vect.y * vect.y;
	float z = vect.z * vect.z;

	return sqrt(x + y + z);
}

bool Static_Cylinder::CheckCollisionCylinder(Dynamic_Cylinder &other)
{
	glm::vec3 distanceVector = position - other.GetPosition();	

	float distance = VectorLength(distanceVector);

	if(distance < radius + other.GetRadius())
	{
		return true;
	}
	else return false;
}

bool Static_Cylinder::CheckCollisionStaticCylinder(Static_Cylinder &other)
{
	glm::vec3 distanceVector = position - other.GetPosition();	

	float distance = VectorLength(distanceVector);

	if(distance < radius + other.GetRadius())
	{
		return true;
	}
	else return false;
}

bool Static_Cylinder::CheckCollisionAABB(Static_AABB &other)
{
	if(position.x >= other.GetMinCorner().x &&
	   position.x <= other.GetMaxCorner().x && 
	   position.z <= other.GetMinCorner().z &&
	   position.z >= other.GetMaxCorner().z)
	{
		return true;
	}
	else return false;
}



Dynamic_Cylinder::Dynamic_Cylinder()
{
	position = glm::vec3();
	velocityVector = glm::vec3();

	radius = 0.0f;
	height = 0.0f;
}
Dynamic_Cylinder::Dynamic_Cylinder(glm::vec3 newPosition,
								   glm::vec3 newVelocityVector,
								   float newRadius, 
								   float newHeight)
{
	assert(newRadius > 0.0f || newHeight > 0.0f);

	position = newPosition;
	velocityVector = newVelocityVector;
	glm::normalize(velocityVector);

	radius = newRadius;
	height = newHeight;
}

bool Dynamic_Cylinder::CheckCollisionCylinder(const Dynamic_Cylinder &other)
{
	glm::vec3 orientationPosition = position + velocityVector;

	glm::vec3 distanceVector = orientationPosition - other.position;	

	float distance = VectorLength(distanceVector);

	if(distance < radius + other.radius)
	{
		return true;
	}
	else return false;
}

bool Dynamic_Cylinder::CheckCollisionStaticCylinder(Static_Cylinder &other)
{
	glm::vec3 orientationPosition = position + velocityVector;

	glm::vec3 distanceVector = orientationPosition - other.GetPosition();	

	float distance = VectorLength(distanceVector);

	if(distance < radius + other.GetRadius())
	{
		return true;
	}
	else return false;
}

bool Dynamic_Cylinder::CheckCollisionAABB(Static_AABB &other)
{
	glm::vec3 orientationPosition = position + velocityVector;

	if(orientationPosition.x >= other.GetMinCorner().x &&
	   orientationPosition.x <= other.GetMaxCorner().x && 
	   orientationPosition.z <= other.GetMinCorner().z &&
	   orientationPosition.z >= other.GetMaxCorner().z)
	{
		return true;
	}
	else return false;
}