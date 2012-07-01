#include "Entities.h"

EntityTreasure::EntityTreasure()
{
	meshData = NULL;
	orbitingCube = NULL;
	collisionVolume = Static_Cylinder();
	position = glm::vec3();
	points = 0;
	animMovementY = 0.01f;
	animAngleY_degs = 1.0f;
	orbitAngle_degs = 10.0f;
	hasCollisionVolume = false;
	isRemoved = false;
}
EntityTreasure::EntityTreasure(glm::vec3 newPosition, int newPoints)
{
	meshData = NULL;
	orbitingCube = NULL;
	collisionVolume = Static_Cylinder();
	position = newPosition;
	points = newPoints;
	animMovementY = 0.01f;
	animAngleY_degs = 1.0f;
	orbitAngle_degs = 10.0f;
	hasCollisionVolume = false;
	isRemoved = false;
}

EntityTreasure::EntityTreasure(const EntityTreasure &other)
{
	meshData = new Framework::Mesh(*other.meshData);
	orbitingCube = new Framework::Mesh(*other.orbitingCube);
	
	collisionVolume = other.collisionVolume;
	position = other.position;
	points = other.points;

	animMovementY = other.animMovementY;
	animAngleY_degs = other.animAngleY_degs;
	orbitAngle_degs = other.orbitAngle_degs;

	hasCollisionVolume = other.hasCollisionVolume;
	isRemoved = other.isRemoved;
}
EntityTreasure::~EntityTreasure()
{
	if(meshData != NULL)
	{
		delete meshData;
		meshData = NULL;
	}
	if(orbitingCube != NULL)
	{
		delete orbitingCube;
		orbitingCube = NULL;
	}
}
EntityTreasure EntityTreasure::operator=(const EntityTreasure &other)
{
	if(this == &other)
	{
		return *this;
	}

	meshData = new Framework::Mesh(*other.meshData);
	orbitingCube = new Framework::Mesh(*other.orbitingCube);
	
	collisionVolume = other.collisionVolume;
	position = other.position;
	points = other.points;

	animMovementY = other.animMovementY;
	animAngleY_degs = other.animAngleY_degs;
	orbitAngle_degs = other.orbitAngle_degs;

	hasCollisionVolume = other.hasCollisionVolume;
	isRemoved = other.isRemoved;

	return *this;
}

void EntityTreasure::LoadMesh(const std::string &fileName)
{
	try
	{
		meshData = new Framework::Mesh(fileName);
		orbitingCube = new Framework::Mesh(fileName);
	}
	catch(std::exception &ex)
	{
		printf("%s\n", ex.what());
		throw;
	}
}

void EntityTreasure::AttachCollisionVolume(const Static_Cylinder &newCollisionVolume)
{
	collisionVolume = newCollisionVolume;
	hasCollisionVolume = true;
}
void EntityTreasure::AttachCollisionVolume(float radius, float height)
{
	collisionVolume = Static_Cylinder(position, radius, height);	
	hasCollisionVolume = true;
}
void EntityTreasure::DetachCollisionVolume()
{
	collisionVolume = Static_Cylinder();
	hasCollisionVolume = false;
}

void EntityTreasure::DetectCollisions(Dynamic_Cylinder playerVolume)
{
	if(playerVolume.CheckCollisionStaticCylinder(collisionVolume) == true)
	{
		this->Remove();
	}
}

void EntityTreasure::Spawn(Static_AABB parthenonBaseVolume, 
						   Dynamic_Cylinder *treeVolumes, int treeVolumesCount, 
						   Dynamic_Cylinder playerVolume)
{
	bool hasSpace = false;
	
	while(!hasSpace)
	{
		position.x = rand() % 100 - 50;
		position.y = 0.5f;
		position.z = rand() % 100 - 50;

		// TODO: Not flexible. Hard coded values.
		this->AttachCollisionVolume(1.0f, 1.0f);

		if(playerVolume.CheckCollisionStaticCylinder(collisionVolume) == false)
		{
			hasSpace = true;
		}

		for(int tree = 0; tree < treeVolumesCount; tree++)
		{
			if(collisionVolume.CheckCollisionCylinder(treeVolumes[tree]) == false)
			{
				hasSpace = true;
			}
		}
	
		if(collisionVolume.CheckCollisionAABB(parthenonBaseVolume) == false)
		{
			hasSpace = true;
		}
	}

	isRemoved = false;
}

void EntityTreasure::Update()
{
	this->UpdateAnimation();
}
void EntityTreasure::UpdateAnimation()
{
	position.y += animMovementY;

	if(position.y >= 1.0f)
	{
		animMovementY *= -1;
	}
	if(position.y <= 0.5f)
	{
		animMovementY *= -1;
	}
	
	animAngleY_degs++;

	if(animAngleY_degs >= 360.0f)
	{
		animAngleY_degs = 0.0f;
	}
	else if(animAngleY_degs <= 0.0f)
	{
		animAngleY_degs = 360.0f;
	}

	orbitAngle_degs += 5;

	if(orbitAngle_degs >= 360.0f)
	{
		orbitAngle_degs = 0.0f;
	}
	else if(orbitAngle_degs <= 0.0f)
	{
		orbitAngle_degs = 360.0f;
	}
}

void EntityTreasure::Render(ProgramData uniformColorTint, glutil::MatrixStack &modelMatrix)
{
	glutil::PushStack push(modelMatrix);

	modelMatrix.Translate(position);
	modelMatrix.RotateX(45.0f);
	modelMatrix.RotateY(animAngleY_degs);
	modelMatrix.RotateZ(45.0f);	
	modelMatrix.Scale(0.5f);

	glUseProgram(uniformColorTint.theProgram);
	glUniformMatrix4fv(uniformColorTint.modelToCameraMatrixUnif, 1, GL_FALSE, glm::value_ptr(modelMatrix.Top()));
	glUniform4f(uniformColorTint.baseColorUnif, 0.9f, 0.2f, 0.0f, 0.9f);
	meshData->Render();

	// Render orbiting cube
	{
		glutil::PushStack push(modelMatrix);
			
		modelMatrix.RotateX(orbitAngle_degs + 1.35f);
		modelMatrix.Translate(0.0f, 1.0f, 0.0f);	
		modelMatrix.Scale(0.2f);		

		glUseProgram(uniformColorTint.theProgram);
		glUniformMatrix4fv(uniformColorTint.modelToCameraMatrixUnif, 1, GL_FALSE, glm::value_ptr(modelMatrix.Top()));
		glUniform4f(uniformColorTint.baseColorUnif, 0.0f, 0.2f, 0.9f, 0.9f);
		orbitingCube->Render();
	}

	// Render other orbiting cube
	{
		glutil::PushStack push(modelMatrix);

		modelMatrix.RotateY(orbitAngle_degs - 0.9f);
		modelMatrix.Translate(0.0f, 0.0f, 1.0f);
		modelMatrix.Scale(0.2f);

		glUseProgram(uniformColorTint.theProgram);
		glUniformMatrix4fv(uniformColorTint.modelToCameraMatrixUnif, 1, GL_FALSE, glm::value_ptr(modelMatrix.Top()));
		glUniform4f(uniformColorTint.baseColorUnif, 0.3f, 0.2f, 0.3f, 0.9f);
		orbitingCube->Render();
	}

	// Render third oribiting cube
	{
		glutil::PushStack push(modelMatrix);

		modelMatrix.RotateZ(orbitAngle_degs + 0.2f);
		modelMatrix.Translate(1.0f, 0.0f, 0.0f);
		modelMatrix.Scale(0.2f);

		glUseProgram(uniformColorTint.theProgram);
		glUniformMatrix4fv(uniformColorTint.modelToCameraMatrixUnif, 1, GL_FALSE, glm::value_ptr(modelMatrix.Top()));
		glUniform4f(uniformColorTint.baseColorUnif, 0.5f, 0.2f, 0.9f, 0.9f);
		orbitingCube->Render();
	}

	// Render third oribiting cube
	{
		glutil::PushStack push(modelMatrix);

		modelMatrix.RotateZ(orbitAngle_degs - 100.0f);
		modelMatrix.Translate(1.0f, 0.0f, 0.0f);
		modelMatrix.Scale(0.2f);

		glUseProgram(uniformColorTint.theProgram);
		glUniformMatrix4fv(uniformColorTint.modelToCameraMatrixUnif, 1, GL_FALSE, glm::value_ptr(modelMatrix.Top()));
		glUniform4f(uniformColorTint.baseColorUnif, 0.6f, 0.0f, 0.9f, 0.9f);
		orbitingCube->Render();
	}

	// Render orbiting cube
	{
		glutil::PushStack push(modelMatrix);
			
		modelMatrix.RotateX(orbitAngle_degs - 100.0f);
		modelMatrix.Translate(0.0f, 1.0f, 0.0f);	
		modelMatrix.Scale(0.2f);		

		glUseProgram(uniformColorTint.theProgram);
		glUniformMatrix4fv(uniformColorTint.modelToCameraMatrixUnif, 1, GL_FALSE, glm::value_ptr(modelMatrix.Top()));
		glUniform4f(uniformColorTint.baseColorUnif, 0.9f, 0.2f, 0.5f, 0.9f);
		orbitingCube->Render();
	}

	// Render other orbiting cube
	{
		glutil::PushStack push(modelMatrix);

		modelMatrix.RotateY(orbitAngle_degs - 100.0f);
		modelMatrix.Translate(0.0f, 0.0f, 1.0f);
		modelMatrix.Scale(0.2f);

		glUseProgram(uniformColorTint.theProgram);
		glUniformMatrix4fv(uniformColorTint.modelToCameraMatrixUnif, 1, GL_FALSE, glm::value_ptr(modelMatrix.Top()));
		glUniform4f(uniformColorTint.baseColorUnif, 0.1f, 0.2f, 0.0f, 0.9f);
		orbitingCube->Render();
	}

	glUseProgram(0);
}

bool EntityTreasure::IsRemoved()
{
	return isRemoved;
}

void EntityTreasure::Remove()
{
	isRemoved = true;
}