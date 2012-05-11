#ifdef MOUSE_EXPORTS
#define MOUSE_API __declspec(dllexport)
#else
#define MOUSE_API __declspec(dllimport)
#endif

#pragma once

#include <gl/freeglut.h>

#include "../GraphicsGeometry/Vector.h"

class MOUSE_API Mouse
{
private:
	Vector3d currentPosition;
	Vector3d lastPosition;

	bool isLeftBtnPressed;
	bool isRightBtnPressed;

	bool isMouseWheelUp;
	bool isMouseWheelDown;

public:
	Mouse();

	bool IsLeftButtonDown();
	bool IsRightButtonDown();

	bool IsMouseWheelDown();
	bool IsMouseWheelUp();

	void PressLeftButton();
	void ReleaseLeftButton();
	void PressRightButton();
	void ReleaseRightButton();

	void MouseWheelDown();
	void MouseWheelNotDown();
	void MouseWheelUp();
	void MouseWheelNotUp();

	void SetCurrentPosition(Vector3d newPosition);
	Vector3d GetCurrentPosition();
	Vector3d GetLastPosition();

	void OverrideLastPosition(Vector3d lastPosition);

	Vector3d static ConvertMouseToOGLCoordinate(int mouseX, int mouseY, int mouseZ = 0.0f);
};