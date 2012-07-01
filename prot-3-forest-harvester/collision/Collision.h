#ifdef COLLISION_EXPORTS
#define COLLISION_API __declspec(dllexport)
#else
#define COLLISION_API __declspec(dllimport)
#endif

#ifndef COLLISION_H
#define COLLISION_H

#include <glm/glm.hpp>

class COLLISION_API Dynamic_Cylinder;

class COLLISION_API Static_AABB
{
private:
	glm::vec3 minCorner;
	glm::vec3 maxCorner;

public:
	Static_AABB();
	Static_AABB(glm::vec3 newMinCorner, glm::vec3 newMaxCorner);

	glm::vec3 GetMinCorner();
	glm::vec3 GetMaxCorner();
};

inline Static_AABB::Static_AABB()
{
	minCorner = glm::vec3();
	maxCorner = glm::vec3();
}
inline Static_AABB::Static_AABB(glm::vec3 newMinCorner, glm::vec3 newMaxCorner)
{
	minCorner = newMinCorner;
	maxCorner = newMaxCorner;
}

inline glm::vec3 Static_AABB::GetMinCorner()
{
	return minCorner;
}
inline glm::vec3 Static_AABB::GetMaxCorner()
{
	return maxCorner;
}


class COLLISION_API Static_Cylinder
{
private:
	glm::vec3 position;
	
	float radius;
	float height;

public:
	Static_Cylinder();
	Static_Cylinder(glm::vec3 newPosition, float newRadius, float newHeight);
	
	bool CheckCollisionCylinder(Dynamic_Cylinder &other);
	bool CheckCollisionStaticCylinder(Static_Cylinder &other);
	bool CheckCollisionAABB(Static_AABB &other);

	glm::vec3 GetPosition();
	float GetRadius();
	float GetHeight();
};

inline Static_Cylinder::Static_Cylinder()
{
	position = glm::vec3();

	radius = 0.0f;
	height = 0.0f;
}
inline Static_Cylinder::Static_Cylinder(glm::vec3 newPosition, float newRadius, float newHeight)
{
	position = newPosition;
	
	radius = newRadius;
	height = newHeight;
}

inline glm::vec3 Static_Cylinder::GetPosition()
{
	return position;
}
inline float Static_Cylinder::GetRadius()
{
	return radius;
}
inline float Static_Cylinder::GetHeight()
{
	return height;
}



class COLLISION_API Dynamic_Cylinder
{
private:
	glm::vec3 position;
	glm::vec3 velocityVector;

	float radius;
	float height;

public:
	Dynamic_Cylinder();
	Dynamic_Cylinder(glm::vec3 newPosition, glm::vec3 newVelocityVector,
					 float newRadius, float newHeight);

	bool CheckCollisionCylinder(const Dynamic_Cylinder &other);
	bool CheckCollisionStaticCylinder(Static_Cylinder &other);
	bool CheckCollisionAABB(Static_AABB &other);

	void SetPosition(glm::vec3 newPosition);
	void SetVelocity(glm::vec3 newVelocityVector);

	void SetRadius(float newRadius);
	void SetHeight(float newHeight);

	glm::vec3 GetPosition();

	float GetRadius();
	float GetHeight();
};

inline void Dynamic_Cylinder::SetPosition(glm::vec3 newPosition)
{
	position = newPosition;
}
inline void Dynamic_Cylinder::SetVelocity(glm::vec3 newVelocityVector)
{
	velocityVector = newVelocityVector;
	glm::normalize(velocityVector);

	position += velocityVector;
}
inline void Dynamic_Cylinder::SetRadius(float newRadius)
{
	assert(newRadius > 0.0f);
	radius = newRadius;
}
inline void Dynamic_Cylinder::SetHeight(float newHeight)
{
	assert(newHeight > 0.0f);
	height = newHeight;
}

inline glm::vec3 Dynamic_Cylinder::GetPosition()
{
	return position;
}

inline float Dynamic_Cylinder::GetRadius()
{
	return radius;
}
inline float Dynamic_Cylinder::GetHeight()
{
	return height;
}

#endif