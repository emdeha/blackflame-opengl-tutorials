#ifndef ENTITIES_H
#define ENTITIES_H


#include <glload/gl_3_3.h>
#include <glutil/glutil.h>
#include <GL/freeglut.h>
#include "../framework/framework.h"
#include "../framework/Mesh.h"


#include <glm/glm.hpp>
#include "../Collision/Collision.h"

#include "ProgramData.h"

class EntityTreasure
{
private:
	Framework::Mesh *meshData;
	Framework::Mesh *orbitingCube;

	Static_Cylinder collisionVolume;

	glm::vec3 position;

	int points;

	float animMovementY;
	float animAngleY_degs;
	float orbitAngle_degs;

	bool hasCollisionVolume;
	bool isRemoved;

public:
	EntityTreasure();
	EntityTreasure(glm::vec3 newPosition, int newPoints);
	
	void LoadMesh(const std::string &fileName);

	void AttachCollisionVolume(const Static_Cylinder &newCollisionVolume);
	void AttachCollisionVolume(float radius, float height);
	void DetachCollisionVolume();

	void DetectCollisions(Dynamic_Cylinder playerVolume);

	void Spawn(Static_AABB parthenonBaseVolume, 
			   Dynamic_Cylinder *treeVolumes, int treeVolumesCount, 
			   Dynamic_Cylinder playerVolume);

	void Update();
	void Render(ProgramData uniformColorTint, glutil::MatrixStack &modelMatrix);

	void Remove();

	bool IsRemoved();

	void SetPoints(int newPoints)
	{
		points = newPoints;
	}

public:
	EntityTreasure(const EntityTreasure &other);
	~EntityTreasure();
	EntityTreasure operator=(const EntityTreasure &other);

private:
	void UpdateAnimation();
};

#endif