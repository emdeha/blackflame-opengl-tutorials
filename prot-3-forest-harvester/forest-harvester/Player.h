#ifndef PLAYER_H
#define PLAYER_H


#include <glm/glm.hpp>

#include "../Collision/Collision.h"
#include "../Camera/Camera.h"

class Player
{
private:
	Camera playerCamera;
	Dynamic_Cylinder collisionVolume;

	glm::vec3 position;
	glm::vec3 velocity;

	bool hasCamera;
	bool hasCollisionVolume;

public:
	Player();
	Player(glm::vec3 newPosition, glm::vec3 newVelocity);

	void AttachCollisionVolume_Cylinder(float radius = 1.5f, float height = 2.0f);
	void DetachCollisionVolume_Cylinder();

	void AttachCamera(const Camera &newCamera);
	void DetachCamera(); // ?

	Camera &AcquireCamera(); // Maybe there is a better design decision

	Dynamic_Cylinder GetCollisionVolume();

	void LookLeft(float angle_degs);
	void LookRight(float angle_degs);
	void LookUp(float angle_degs);
	void LookDown(float angle_degs);

	void MoveForward(float units, Dynamic_Cylinder *treeVolumes, 
								  int treeVolumesCount,
								  Static_AABB parthenonBaseVolume);
	void MoveBackward(float units, Dynamic_Cylinder *treeVolumes,
								   int treeVolumesCount,
								   Static_AABB parthenonBaseVolume);
	void MoveLeft(float units, Dynamic_Cylinder *treeVolumes,
							   int treeVolumesCount,
							   Static_AABB parthenonBaseVolume);
	void MoveRight(float units, Dynamic_Cylinder *treeVolumes,
								int treeVolumesCount,
								Static_AABB parthenonBaseVolume);

private:
	bool CheckCollisions(Dynamic_Cylinder *treeVolumes, int treeVolumesCount,
						 Static_AABB parthenonBaseVolume);
};


#endif