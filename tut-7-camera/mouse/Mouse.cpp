#include "stdafx.h"
#include "Mouse.h"

Mouse::Mouse()
{
	currentPosition = glm::vec3();
	lastPosition = glm::vec3();

	isLeftButtonPressed = false;
	isRightButtonPressed = false;

	isMouseWheelUp = false;
	isMouseWheelDown = false;
}

inline void Mouse::SetCurrentPosition(glm::vec3 newCurrentPosition)
{
	currentPosition = newCurrentPosition;
}

inline glm::vec3 Mouse::GetCurrentPosition()
{
	return currentPosition;
}
inline glm::vec3 Mouse::GetLastPosition()
{
	return lastPosition;
}

inline void Mouse::OverrideLastPosition(glm::vec3 newLastPosition)
{
	lastPosition = newLastPosition;
}


inline bool Mouse::IsLeftButtonDown()
{
	return isLeftButtonPressed;
}
inline bool Mouse::IsRightButtonDown()
{
	return isRightButtonPressed;
}

inline bool Mouse::IsMouseWheelUp()
{
	return isMouseWheelUp;
}
inline bool Mouse::IsMouseWheelDown()
{
	return isMouseWheelDown;
}

inline void Mouse::PressLeftButton()
{
	isLeftButtonPressed = true;
}
inline void Mouse::ReleaseLeftButton()
{
	isLeftButtonPressed = false;
}
inline void Mouse::PressRightButton()
{
	isRightButtonPressed = true;
}
inline void Mouse::ReleaseRightButton()
{
	isRightButtonPressed = false;
}

inline void Mouse::MouseWheelUp()
{
	isMouseWheelUp = true;
}
inline void Mouse::MouseWheelNotUp()
{
	isMouseWheelUp = false;
}
inline void Mouse::MouseWheelDown()
{
	isMouseWheelDown = true;
}
inline void Mouse::MouseWheelNotDown()
{
	isMouseWheelDown = false;
}