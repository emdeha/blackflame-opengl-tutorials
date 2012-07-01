#include "Player.h"

Player::Player()
{
	playerCamera = Camera();
	collisionVolume = Dynamic_Cylinder();

	position = glm::vec3();
	velocity = glm::vec3();

	hasCamera = false;
	hasCollisionVolume = false;
}
Player::Player(glm::vec3 newPosition, glm::vec3 newVelocity)
{
	playerCamera = Camera();
	collisionVolume = Dynamic_Cylinder();

	position = newPosition;
	velocity = newVelocity;

	hasCamera = false;
	hasCollisionVolume = false;
}

void Player::AttachCollisionVolume_Cylinder(float radius, float height)
{
	collisionVolume.SetPosition(position);
	collisionVolume.SetHeight(height);
	collisionVolume.SetRadius(radius);

	hasCollisionVolume = true;
}
void Player::DetachCollisionVolume_Cylinder()
{
	collisionVolume = Dynamic_Cylinder();

	hasCollisionVolume = false;
}

void Player::AttachCamera(const Camera &camera)
{
	playerCamera = camera;
	hasCamera = true;
}
void Player::DetachCamera()
{
	playerCamera = Camera();
	hasCamera = false;
}

Camera &Player::AcquireCamera()
{
	return playerCamera;
}

Dynamic_Cylinder Player::GetCollisionVolume()
{
	return collisionVolume;
}

void Player::LookDown(float angle_degs)
{
	if(hasCamera)
	{
		playerCamera.LookDown(angle_degs);
	}
}
void Player::LookUp(float angle_degs)
{
	if(hasCamera)
	{
		playerCamera.LookUp(angle_degs);		
	}
}
void Player::LookLeft(float angle_degs)
{
	if(hasCamera)
	{
		playerCamera.LookLeft(angle_degs);		
	}
}
void Player::LookRight(float angle_degs)
{
	if(hasCamera)
	{
		playerCamera.LookRight(angle_degs);
	}
}

void Player::MoveForward(float units, Dynamic_Cylinder *treeVolumes, int treeVolumesCount, 
									  Static_AABB parthenonBaseVolume)
{
	if(hasCollisionVolume)
	{
		if(this->CheckCollisions(treeVolumes, treeVolumesCount, parthenonBaseVolume))
		{
			playerCamera.MoveForward(units);
		}
	}
	else
	{
		playerCamera.MoveForward(units);
	}
	
	position = playerCamera.GetPosition();
	velocity = playerCamera.GetForwardVector();

	collisionVolume.SetPosition(playerCamera.GetPosition());
	collisionVolume.SetVelocity(playerCamera.GetForwardVector());
}
void Player::MoveBackward(float units, Dynamic_Cylinder *treeVolumes, int treeVolumesCount, 
									   Static_AABB parthenonBaseVolume)
{
	if(hasCollisionVolume)
	{
		if(this->CheckCollisions(treeVolumes, treeVolumesCount, parthenonBaseVolume))
		{
			playerCamera.MoveBackward(units);
		}
	}
	else
	{
		playerCamera.MoveBackward(units);
	}
	
	position = playerCamera.GetPosition();
	velocity = -playerCamera.GetForwardVector();

	collisionVolume.SetPosition(playerCamera.GetPosition());
	collisionVolume.SetVelocity(-playerCamera.GetForwardVector());
}
void Player::MoveRight(float units, Dynamic_Cylinder *treeVolumes, int treeVolumesCount, 
									Static_AABB parthenonBaseVolume)
{
	if(hasCollisionVolume)
	{
		if(this->CheckCollisions(treeVolumes, treeVolumesCount, parthenonBaseVolume))
		{
			playerCamera.MoveRight(units);
		}
	}
	else
	{
		playerCamera.MoveRight(units);
	}
	
	position = playerCamera.GetPosition();
	velocity = playerCamera.GetRightVector();

	collisionVolume.SetPosition(playerCamera.GetPosition());
	collisionVolume.SetVelocity(playerCamera.GetRightVector());
}
void Player::MoveLeft(float units, Dynamic_Cylinder *treeVolumes, int treeVolumesCount, 
								   Static_AABB parthenonBaseVolume)
{
	if(hasCollisionVolume)
	{
		if(this->CheckCollisions(treeVolumes, treeVolumesCount, parthenonBaseVolume))
		{
			playerCamera.MoveLeft(units);
		}
	}
	else
	{
		playerCamera.MoveLeft(units);
	}
	
	position = playerCamera.GetPosition();
	velocity = -playerCamera.GetRightVector();

	collisionVolume.SetPosition(playerCamera.GetPosition());
	collisionVolume.SetVelocity(-playerCamera.GetRightVector());
}


bool Player::CheckCollisions(Dynamic_Cylinder *treeVolumes, int treeVolumesCount,
							 Static_AABB parthenonBaseVolume)
{
	bool isFree = true;

	for(int tree = 0; tree < treeVolumesCount; tree++)
	{
		if(collisionVolume.CheckCollisionCylinder(treeVolumes[tree]) == true)
		{
			isFree = false;
		}
	}
	if(collisionVolume.CheckCollisionAABB(parthenonBaseVolume) == true)
	{
		isFree = false;
	}

	return isFree;
}