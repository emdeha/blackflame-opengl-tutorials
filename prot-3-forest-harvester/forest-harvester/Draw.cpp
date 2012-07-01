#include "Draw.h"

const float g_fColumnBaseHeight = 0.25f;

const float g_fParthenonWidth = 14.0f;
const float g_fParthenonLength = 20.0f;
const float g_fParthenonColumnHeight = 5.0f;
const float g_fParthenonBaseHeight = 1.0f;
const float g_fParthenonTopHeight = 2.0f;


void DrawTree(ProgramData uniformColorTint, glutil::MatrixStack &modelMatrix, float fTrunkHeight, float fConeHeight)
{
	//Draw trunk.
	{
		glutil::PushStack push(modelMatrix);

		modelMatrix.Scale(glm::vec3(1.0f, fTrunkHeight, 1.0f));
		modelMatrix.Translate(glm::vec3(0.0f, 0.5f, 0.0f));

		glUseProgram(uniformColorTint.theProgram);
		glUniformMatrix4fv(uniformColorTint.modelToCameraMatrixUnif, 1, GL_FALSE, glm::value_ptr(modelMatrix.Top()));
		glUniform4f(uniformColorTint.baseColorUnif, 0.694f, 0.4f, 0.106f, 1.0f);
		g_pCylinderMesh->Render();
		glUseProgram(0);
	}

	//Draw the treetop
	{
		glutil::PushStack push(modelMatrix);

		modelMatrix.Translate(glm::vec3(0.0f, fTrunkHeight, 0.0f));
		modelMatrix.Scale(glm::vec3(3.0f, fConeHeight, 3.0f));

		glUseProgram(uniformColorTint.theProgram);
		glUniformMatrix4fv(uniformColorTint.modelToCameraMatrixUnif, 1, GL_FALSE, glm::value_ptr(modelMatrix.Top()));
		glUniform4f(uniformColorTint.baseColorUnif, 0.0f, 1.0f, 0.0f, 1.0f);
		g_pConeMesh->Render();
		glUseProgram(0);
	}
}


void DrawForest(ProgramData uniformColorTint, glutil::MatrixStack &modelMatrix, glutil::MatrixStack camMatrix)
{
	for(int iTree = 0; iTree < ARRAY_COUNT(g_forest); iTree++)
	{
		const TreeData &currTree = g_forest[iTree];

		glutil::PushStack push(modelMatrix);
		modelMatrix.ApplyMatrix(camMatrix.Top());

		modelMatrix.Translate(glm::vec3(currTree.fXPos, 0.0f, currTree.fZPos));
		DrawTree(uniformColorTint, modelMatrix, currTree.fTrunkHeight, currTree.fConeHeight);
	}
}




void DrawColumn(ProgramData uniformColorTint, glutil::MatrixStack &modelMatrix, float fHeight)
{
	//Draw the bottom of the column.
	{
		glutil::PushStack push(modelMatrix);

		modelMatrix.Scale(glm::vec3(1.0f, g_fColumnBaseHeight, 1.0f));
		modelMatrix.Translate(glm::vec3(0.0f, 0.5f, 0.0f));

		glUseProgram(uniformColorTint.theProgram);
		glUniformMatrix4fv(uniformColorTint.modelToCameraMatrixUnif, 1, GL_FALSE, glm::value_ptr(modelMatrix.Top()));
		glUniform4f(uniformColorTint.baseColorUnif, 1.0f, 1.0f, 1.0f, 1.0f);
		g_pCubeTintMesh->Render();
		glUseProgram(0);
	}

	//Draw the top of the column.
	{
		glutil::PushStack push(modelMatrix);

		modelMatrix.Translate(glm::vec3(0.0f, fHeight - g_fColumnBaseHeight, 0.0f));
		modelMatrix.Scale(glm::vec3(1.0f, g_fColumnBaseHeight, 1.0f));
		modelMatrix.Translate(glm::vec3(0.0f, 0.5f, 0.0f));

		glUseProgram(uniformColorTint.theProgram);
		glUniformMatrix4fv(uniformColorTint.modelToCameraMatrixUnif, 1, GL_FALSE, glm::value_ptr(modelMatrix.Top()));
		glUniform4f(uniformColorTint.baseColorUnif, 0.9f, 0.9f, 0.9f, 0.9f);
		g_pCubeTintMesh->Render();
		glUseProgram(0);
	}

	//Draw the main column.
	{
		glutil::PushStack push(modelMatrix);

		modelMatrix.Translate(glm::vec3(0.0f, g_fColumnBaseHeight, 0.0f));
		modelMatrix.Scale(glm::vec3(0.8f, fHeight - (g_fColumnBaseHeight * 2.0f), 0.8f));
		modelMatrix.Translate(glm::vec3(0.0f, 0.5f, 0.0f));

		glUseProgram(uniformColorTint.theProgram);
		glUniformMatrix4fv(uniformColorTint.modelToCameraMatrixUnif, 1, GL_FALSE, glm::value_ptr(modelMatrix.Top()));
		glUniform4f(uniformColorTint.baseColorUnif, 0.9f, 0.9f, 0.9f, 0.9f);
		g_pCylinderMesh->Render();
		glUseProgram(0);
	}
}

void DrawParthenon(ProgramData uniformColorTint, ProgramData objectColor, glutil::MatrixStack &modelMatrix)
{
	//Draw base.
	{
		glutil::PushStack push(modelMatrix);

		modelMatrix.Scale(glm::vec3(g_fParthenonWidth, g_fParthenonBaseHeight, g_fParthenonLength));
		modelMatrix.Translate(glm::vec3(0.0f, 0.5f, 0.0f));

		glUseProgram(uniformColorTint.theProgram);
		glUniformMatrix4fv(uniformColorTint.modelToCameraMatrixUnif, 1, GL_FALSE, glm::value_ptr(modelMatrix.Top()));
		glUniform4f(uniformColorTint.baseColorUnif, 0.9f, 0.9f, 0.9f, 0.9f);
		g_pCubeTintMesh->Render();
		glUseProgram(0);
	}

	//Draw top.
	{
		glutil::PushStack push(modelMatrix);

		modelMatrix.Translate(glm::vec3(0.0f, g_fParthenonColumnHeight + g_fParthenonBaseHeight, 0.0f));
		modelMatrix.Scale(glm::vec3(g_fParthenonWidth, g_fParthenonTopHeight, g_fParthenonLength));
		modelMatrix.Translate(glm::vec3(0.0f, 0.5f, 0.0f));

		glUseProgram(uniformColorTint.theProgram);
		glUniformMatrix4fv(uniformColorTint.modelToCameraMatrixUnif, 1, GL_FALSE, glm::value_ptr(modelMatrix.Top()));
		glUniform4f(uniformColorTint.baseColorUnif, 0.9f, 0.9f, 0.9f, 0.9f);
		g_pCubeTintMesh->Render();
		glUseProgram(0);
	}

	//Draw columns.
	const float fFrontZVal = (g_fParthenonLength / 2.0f) - 1.0f;
	const float fRightXVal = (g_fParthenonWidth / 2.0f) - 1.0f;

	for(int iColumnNum = 0; iColumnNum < int(g_fParthenonWidth / 2.0f); iColumnNum++)
	{
		{
			glutil::PushStack push(modelMatrix);
			modelMatrix.Translate(glm::vec3((2.0f * iColumnNum) - (g_fParthenonWidth / 2.0f) + 1.0f,
				g_fParthenonBaseHeight, fFrontZVal));

			DrawColumn(uniformColorTint, modelMatrix, g_fParthenonColumnHeight);
		}
		{
			glutil::PushStack push(modelMatrix);
			modelMatrix.Translate(glm::vec3((2.0f * iColumnNum) - (g_fParthenonWidth / 2.0f) + 1.0f,
				g_fParthenonBaseHeight, -fFrontZVal));

			DrawColumn(uniformColorTint, modelMatrix, g_fParthenonColumnHeight);
		}
	}

	//Don't draw the first or last columns, since they've been drawn already.
	for(int iColumnNum = 1; iColumnNum < int((g_fParthenonLength - 2.0f) / 2.0f); iColumnNum++)
	{
		{
			glutil::PushStack push(modelMatrix);
			modelMatrix.Translate(glm::vec3(fRightXVal,
				g_fParthenonBaseHeight, (2.0f * iColumnNum) - (g_fParthenonLength / 2.0f) + 1.0f));

			DrawColumn(uniformColorTint, modelMatrix, g_fParthenonColumnHeight);
		}
		{
			glutil::PushStack push(modelMatrix);
			modelMatrix.Translate(glm::vec3(-fRightXVal,
				g_fParthenonBaseHeight, (2.0f * iColumnNum) - (g_fParthenonLength / 2.0f) + 1.0f));

			DrawColumn(uniformColorTint, modelMatrix, g_fParthenonColumnHeight);
		}
	}

	//Draw interior.
	{
		glutil::PushStack push(modelMatrix);

		modelMatrix.Translate(glm::vec3(0.0f, 1.0f, 0.0f));
		modelMatrix.Scale(glm::vec3(g_fParthenonWidth - 6.0f, g_fParthenonColumnHeight,
			g_fParthenonLength - 6.0f));
		modelMatrix.Translate(glm::vec3(0.0f, 0.5f, 0.0f));

		glUseProgram(objectColor.theProgram);
		glUniformMatrix4fv(objectColor.modelToCameraMatrixUnif, 1, GL_FALSE, glm::value_ptr(modelMatrix.Top()));
		g_pCubeColorMesh->Render();
		glUseProgram(0);
	}

	//Draw headpiece.
	{
		glutil::PushStack push(modelMatrix);

		modelMatrix.Translate(glm::vec3(
			0.0f,
			g_fParthenonColumnHeight + g_fParthenonBaseHeight + (g_fParthenonTopHeight / 2.0f),
			g_fParthenonLength / 2.0f));
		modelMatrix.RotateX(-135.0f);
		modelMatrix.RotateY(45.0f);

		glUseProgram(objectColor.theProgram);
		glUniformMatrix4fv(objectColor.modelToCameraMatrixUnif, 1, GL_FALSE, glm::value_ptr(modelMatrix.Top()));
		g_pCubeColorMesh->Render();
		glUseProgram(0);
	}
}