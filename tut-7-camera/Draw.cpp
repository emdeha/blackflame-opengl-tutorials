#include "Draw.h"

const float g_fColumnBaseHeight = 0.25f;

const float g_fParthenonWidth = 14.0f;
const float g_fParthenonLength = 20.0f;
const float g_fParthenonColumnHeight = 5.0f;
const float g_fParthenonBaseHeight = 1.0f;
const float g_fParthenonTopHeight = 2.0f;

struct TreeData
{
	float fXPos;
	float fZPos;
	float fTrunkHeight;
	float fConeHeight;
};

static const TreeData g_forest[] =
{
	{-45.0f, -40.0f, 2.0f, 3.0f},
	{-42.0f, -35.0f, 2.0f, 3.0f},
	{-39.0f, -29.0f, 2.0f, 4.0f},
	{-44.0f, -26.0f, 3.0f, 3.0f},
	{-40.0f, -22.0f, 2.0f, 4.0f},
	{-36.0f, -15.0f, 3.0f, 3.0f},
	{-41.0f, -11.0f, 2.0f, 3.0f},
	{-37.0f, -6.0f, 3.0f, 3.0f},
	{-45.0f, 0.0f, 2.0f, 3.0f},
	{-39.0f, 4.0f, 3.0f, 4.0f},
	{-36.0f, 8.0f, 2.0f, 3.0f},
	{-44.0f, 13.0f, 3.0f, 3.0f},
	{-42.0f, 17.0f, 2.0f, 3.0f},
	{-38.0f, 23.0f, 3.0f, 4.0f},
	{-41.0f, 27.0f, 2.0f, 3.0f},
	{-39.0f, 32.0f, 3.0f, 3.0f},
	{-44.0f, 37.0f, 3.0f, 4.0f},
	{-36.0f, 42.0f, 2.0f, 3.0f},

	{-32.0f, -45.0f, 2.0f, 3.0f},
	{-30.0f, -42.0f, 2.0f, 4.0f},
	{-34.0f, -38.0f, 3.0f, 5.0f},
	{-33.0f, -35.0f, 3.0f, 4.0f},
	{-29.0f, -28.0f, 2.0f, 3.0f},
	{-26.0f, -25.0f, 3.0f, 5.0f},
	{-35.0f, -21.0f, 3.0f, 4.0f},
	{-31.0f, -17.0f, 3.0f, 3.0f},
	{-28.0f, -12.0f, 2.0f, 4.0f},
	{-29.0f, -7.0f, 3.0f, 3.0f},
	{-26.0f, -1.0f, 2.0f, 4.0f},
	{-32.0f, 6.0f, 2.0f, 3.0f},
	{-30.0f, 10.0f, 3.0f, 5.0f},
	{-33.0f, 14.0f, 2.0f, 4.0f},
	{-35.0f, 19.0f, 3.0f, 4.0f},
	{-28.0f, 22.0f, 2.0f, 3.0f},
	{-33.0f, 26.0f, 3.0f, 3.0f},
	{-29.0f, 31.0f, 3.0f, 4.0f},
	{-32.0f, 38.0f, 2.0f, 3.0f},
	{-27.0f, 41.0f, 3.0f, 4.0f},
	{-31.0f, 45.0f, 2.0f, 4.0f},
	{-28.0f, 48.0f, 3.0f, 5.0f},

	{-25.0f, -48.0f, 2.0f, 3.0f},
	{-20.0f, -42.0f, 3.0f, 4.0f},
	{-22.0f, -39.0f, 2.0f, 3.0f},
	{-19.0f, -34.0f, 2.0f, 3.0f},
	{-23.0f, -30.0f, 3.0f, 4.0f},
	{-24.0f, -24.0f, 2.0f, 3.0f},
	{-16.0f, -21.0f, 2.0f, 3.0f},
	{-17.0f, -17.0f, 3.0f, 3.0f},
	{-25.0f, -13.0f, 2.0f, 4.0f},
	{-23.0f, -8.0f, 2.0f, 3.0f},
	{-17.0f, -2.0f, 3.0f, 3.0f},
	{-16.0f, 1.0f, 2.0f, 3.0f},
	{-19.0f, 4.0f, 3.0f, 3.0f},
	{-22.0f, 8.0f, 2.0f, 4.0f},
	{-21.0f, 14.0f, 2.0f, 3.0f},
	{-16.0f, 19.0f, 2.0f, 3.0f},
	{-23.0f, 24.0f, 3.0f, 3.0f},
	{-18.0f, 28.0f, 2.0f, 4.0f},
	{-24.0f, 31.0f, 2.0f, 3.0f},
	{-20.0f, 36.0f, 2.0f, 3.0f},
	{-22.0f, 41.0f, 3.0f, 3.0f},
	{-21.0f, 45.0f, 2.0f, 3.0f},

	{-12.0f, -40.0f, 2.0f, 4.0f},
	{-11.0f, -35.0f, 3.0f, 3.0f},
	{-10.0f, -29.0f, 1.0f, 3.0f},
	{-9.0f, -26.0f, 2.0f, 2.0f},
	{-6.0f, -22.0f, 2.0f, 3.0f},
	{-15.0f, -15.0f, 1.0f, 3.0f},
	{-8.0f, -11.0f, 2.0f, 3.0f},
	{-14.0f, -6.0f, 2.0f, 4.0f},
	{-12.0f, 0.0f, 2.0f, 3.0f},
	{-7.0f, 4.0f, 2.0f, 2.0f},
	{-13.0f, 8.0f, 2.0f, 2.0f},
	{-9.0f, 13.0f, 1.0f, 3.0f},
	{-13.0f, 17.0f, 3.0f, 4.0f},
	{-6.0f, 23.0f, 2.0f, 3.0f},
	{-12.0f, 27.0f, 1.0f, 2.0f},
	{-8.0f, 32.0f, 2.0f, 3.0f},
	{-10.0f, 37.0f, 3.0f, 3.0f},
	{-11.0f, 42.0f, 2.0f, 2.0f},


	{15.0f, 5.0f, 2.0f, 3.0f},
	{15.0f, 10.0f, 2.0f, 3.0f},
	{15.0f, 15.0f, 2.0f, 3.0f},
	{15.0f, 20.0f, 2.0f, 3.0f},
	{15.0f, 25.0f, 2.0f, 3.0f},
	{15.0f, 30.0f, 2.0f, 3.0f},
	{15.0f, 35.0f, 2.0f, 3.0f},
	{15.0f, 40.0f, 2.0f, 3.0f},
	{15.0f, 45.0f, 2.0f, 3.0f},

	{25.0f, 5.0f, 2.0f, 3.0f},
	{25.0f, 10.0f, 2.0f, 3.0f},
	{25.0f, 15.0f, 2.0f, 3.0f},
	{25.0f, 20.0f, 2.0f, 3.0f},
	{25.0f, 25.0f, 2.0f, 3.0f},
	{25.0f, 30.0f, 2.0f, 3.0f},
	{25.0f, 35.0f, 2.0f, 3.0f},
	{25.0f, 40.0f, 2.0f, 3.0f},
	{25.0f, 45.0f, 2.0f, 3.0f},
};



void DrawTree(ProgramData data, glutil::MatrixStack &modelMatrix, float fTrunkHeight, float fConeHeight)
{
	//Draw trunk.
	{
		glutil::PushStack push(modelMatrix);

		modelMatrix.Scale(glm::vec3(1.0f, fTrunkHeight, 1.0f));
		modelMatrix.Translate(glm::vec3(0.0f, 0.5f, 0.0f));

		glUseProgram(data.theProgram);
		glUniformMatrix4fv(data.modelToCameraMatrixUnif, 1, GL_FALSE, glm::value_ptr(modelMatrix.Top()));
		glUniform4f(data.baseColorUnif, 0.694f, 0.4f, 0.106f, 1.0f);
		g_pCylinderMesh->Render();
		glUseProgram(0);
	}

	//Draw the treetop
	{
		glutil::PushStack push(modelMatrix);

		modelMatrix.Translate(glm::vec3(0.0f, fTrunkHeight, 0.0f));
		modelMatrix.Scale(glm::vec3(3.0f, fConeHeight, 3.0f));

		glUseProgram(data.theProgram);
		glUniformMatrix4fv(data.modelToCameraMatrixUnif, 1, GL_FALSE, glm::value_ptr(modelMatrix.Top()));
		glUniform4f(data.baseColorUnif, 0.0f, 1.0f, 0.0f, 1.0f);
		g_pConeMesh->Render();
		glUseProgram(0);
	}
}


void DrawForest(ProgramData data, glutil::MatrixStack &modelMatrix, glutil::MatrixStack camMatrix)
{
	for(int iTree = 0; iTree < ARRAY_COUNT(g_forest); iTree++)
	{
		const TreeData &currTree = g_forest[iTree];

		glutil::PushStack push(modelMatrix);
		modelMatrix.ApplyMatrix(camMatrix.Top());

		modelMatrix.Translate(glm::vec3(currTree.fXPos, 0.0f, currTree.fZPos));
		DrawTree(data, modelMatrix, currTree.fTrunkHeight, currTree.fConeHeight);
	}
}




void DrawColumn(ProgramData data, glutil::MatrixStack &modelMatrix, float fHeight)
{
	//Draw the bottom of the column.
	{
		glutil::PushStack push(modelMatrix);

		modelMatrix.Scale(glm::vec3(1.0f, g_fColumnBaseHeight, 1.0f));
		modelMatrix.Translate(glm::vec3(0.0f, 0.5f, 0.0f));

		glUseProgram(data.theProgram);
		glUniformMatrix4fv(data.modelToCameraMatrixUnif, 1, GL_FALSE, glm::value_ptr(modelMatrix.Top()));
		glUniform4f(data.baseColorUnif, 1.0f, 1.0f, 1.0f, 1.0f);
		g_pCubeTintMesh->Render();
		glUseProgram(0);
	}

	//Draw the top of the column.
	{
		glutil::PushStack push(modelMatrix);

		modelMatrix.Translate(glm::vec3(0.0f, fHeight - g_fColumnBaseHeight, 0.0f));
		modelMatrix.Scale(glm::vec3(1.0f, g_fColumnBaseHeight, 1.0f));
		modelMatrix.Translate(glm::vec3(0.0f, 0.5f, 0.0f));

		glUseProgram(data.theProgram);
		glUniformMatrix4fv(data.modelToCameraMatrixUnif, 1, GL_FALSE, glm::value_ptr(modelMatrix.Top()));
		glUniform4f(data.baseColorUnif, 0.9f, 0.9f, 0.9f, 0.9f);
		g_pCubeTintMesh->Render();
		glUseProgram(0);
	}

	//Draw the main column.
	{
		glutil::PushStack push(modelMatrix);

		modelMatrix.Translate(glm::vec3(0.0f, g_fColumnBaseHeight, 0.0f));
		modelMatrix.Scale(glm::vec3(0.8f, fHeight - (g_fColumnBaseHeight * 2.0f), 0.8f));
		modelMatrix.Translate(glm::vec3(0.0f, 0.5f, 0.0f));

		glUseProgram(data.theProgram);
		glUniformMatrix4fv(data.modelToCameraMatrixUnif, 1, GL_FALSE, glm::value_ptr(modelMatrix.Top()));
		glUniform4f(data.baseColorUnif, 0.9f, 0.9f, 0.9f, 0.9f);
		g_pCylinderMesh->Render();
		glUseProgram(0);
	}
}

void DrawParthenon(ProgramData dataColorTint, ProgramData dataObject, glutil::MatrixStack &modelMatrix)
{
	//Draw base.
	{
		glutil::PushStack push(modelMatrix);

		modelMatrix.Scale(glm::vec3(g_fParthenonWidth, g_fParthenonBaseHeight, g_fParthenonLength));
		modelMatrix.Translate(glm::vec3(0.0f, 0.5f, 0.0f));

		glUseProgram(dataColorTint.theProgram);
		glUniformMatrix4fv(dataColorTint.modelToCameraMatrixUnif, 1, GL_FALSE, glm::value_ptr(modelMatrix.Top()));
		glUniform4f(dataColorTint.baseColorUnif, 0.9f, 0.9f, 0.9f, 0.9f);
		g_pCubeTintMesh->Render();
		glUseProgram(0);
	}

	//Draw top.
	{
		glutil::PushStack push(modelMatrix);

		modelMatrix.Translate(glm::vec3(0.0f, g_fParthenonColumnHeight + g_fParthenonBaseHeight, 0.0f));
		modelMatrix.Scale(glm::vec3(g_fParthenonWidth, g_fParthenonTopHeight, g_fParthenonLength));
		modelMatrix.Translate(glm::vec3(0.0f, 0.5f, 0.0f));

		glUseProgram(dataColorTint.theProgram);
		glUniformMatrix4fv(dataColorTint.modelToCameraMatrixUnif, 1, GL_FALSE, glm::value_ptr(modelMatrix.Top()));
		glUniform4f(dataColorTint.baseColorUnif, 0.9f, 0.9f, 0.9f, 0.9f);
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

			DrawColumn(dataColorTint, modelMatrix, g_fParthenonColumnHeight);
		}
		{
			glutil::PushStack push(modelMatrix);
			modelMatrix.Translate(glm::vec3((2.0f * iColumnNum) - (g_fParthenonWidth / 2.0f) + 1.0f,
				g_fParthenonBaseHeight, -fFrontZVal));

			DrawColumn(dataColorTint, modelMatrix, g_fParthenonColumnHeight);
		}
	}

	//Don't draw the first or last columns, since they've been drawn already.
	for(int iColumnNum = 1; iColumnNum < int((g_fParthenonLength - 2.0f) / 2.0f); iColumnNum++)
	{
		{
			glutil::PushStack push(modelMatrix);
			modelMatrix.Translate(glm::vec3(fRightXVal,
				g_fParthenonBaseHeight, (2.0f * iColumnNum) - (g_fParthenonLength / 2.0f) + 1.0f));

			DrawColumn(dataColorTint, modelMatrix, g_fParthenonColumnHeight);
		}
		{
			glutil::PushStack push(modelMatrix);
			modelMatrix.Translate(glm::vec3(-fRightXVal,
				g_fParthenonBaseHeight, (2.0f * iColumnNum) - (g_fParthenonLength / 2.0f) + 1.0f));

			DrawColumn(dataColorTint, modelMatrix, g_fParthenonColumnHeight);
		}
	}

	//Draw interior.
	{
		glutil::PushStack push(modelMatrix);

		modelMatrix.Translate(glm::vec3(0.0f, 1.0f, 0.0f));
		modelMatrix.Scale(glm::vec3(g_fParthenonWidth - 6.0f, g_fParthenonColumnHeight,
			g_fParthenonLength - 6.0f));
		modelMatrix.Translate(glm::vec3(0.0f, 0.5f, 0.0f));

		glUseProgram(dataObject.theProgram);
		glUniformMatrix4fv(dataObject.modelToCameraMatrixUnif, 1, GL_FALSE, glm::value_ptr(modelMatrix.Top()));
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

		glUseProgram(dataObject.theProgram);
		glUniformMatrix4fv(dataObject.modelToCameraMatrixUnif, 1, GL_FALSE, glm::value_ptr(modelMatrix.Top()));
		g_pCubeColorMesh->Render();
		glUseProgram(0);
	}
}