#include "stdafx.h"
#include "Mouse.h"

Mouse::Mouse()
{
	this->currentPosition = Vector3d();
	this->lastPosition = Vector3d();

	this->isLeftBtnPressed = false;
	this->isRightBtnPressed = false;
	this->isMouseWheelDown = false;
	this->isMouseWheelUp = false;
}

bool Mouse::IsLeftButtonDown()
{
	return this->isLeftBtnPressed;
}
bool Mouse::IsRightButtonDown()
{
	return this->isRightBtnPressed;
}
bool Mouse::IsMouseWheelDown()
{
	return this->isMouseWheelDown;
}
bool Mouse::IsMouseWheelUp()
{
	return this->isMouseWheelUp;
}

void Mouse::PressLeftButton()
{
	this->isLeftBtnPressed = true;
}
void Mouse::ReleaseLeftButton()
{
	this->isLeftBtnPressed = false;
}
void Mouse::PressRightButton()
{
	this->isRightBtnPressed = true;
}
void Mouse::ReleaseRightButton()
{
	this->isRightBtnPressed = false;
}

void Mouse::MouseWheelDown()
{
	this->isMouseWheelDown = true;
}
void Mouse::MouseWheelNotDown()
{
	this->isMouseWheelDown = false;
}
void Mouse::MouseWheelUp()
{
	this->isMouseWheelUp = true;
}
void Mouse::MouseWheelNotUp()
{
	this->isMouseWheelUp = false;
}

void Mouse::SetCurrentPosition(Vector3d newPosition)
{
	this->lastPosition = this->currentPosition;
	this->currentPosition = newPosition;
}
Vector3d Mouse::GetCurrentPosition()
{
	return this->currentPosition;
}
Vector3d Mouse::GetLastPosition()
{
	return this->lastPosition;
}

void Mouse::OverrideLastPosition(Vector3d lastPosition)
{
	this->lastPosition = lastPosition;
}

Vector3d Mouse::ConvertMouseToOGLCoordinate(int mouseX, int mouseY, int mouseZ)
{
	int viewport[4];
	double modelMatrix[16];
	double projectionMatrix[16];

	glGetIntegerv(GL_VIEWPORT, viewport);
	glGetDoublev(GL_MODELVIEW_MATRIX, modelMatrix);
	glGetDoublev(GL_PROJECTION_MATRIX, projectionMatrix);

	float winY = float(viewport[3] - mouseY);
	
	double x, y, z;
	gluUnProject((double)mouseX, winY, (double)mouseZ, 
		modelMatrix, projectionMatrix, viewport,
		&x, &y, &z);

	return Vector3d(x, y, z);
}