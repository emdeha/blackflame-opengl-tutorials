#ifdef MOUSE_EXPORTS
#define MOUSE_API __declspec(dllexport)
#else
#define MOUSE_API __declspec(dllimport)
#endif

#include <glm\glm.hpp>

// A simple mouse wrapping class.
class MOUSE_API Mouse
{
private:
	glm::vec3 currentPosition;
	glm::vec3 lastPosition;

	bool isLeftButtonPressed;
	bool isRightButtonPressed;

	bool isMouseWheelUp;
	bool isMouseWheelDown;

public:
	Mouse();

	
	void SetCurrentPosition(glm::vec3 newCurrentPosition);
	glm::vec3 GetCurrentPosition();
	glm::vec3 GetLastPosition();

	void OverrideLastPosition(glm::vec3 newLastPosition);


	bool IsLeftButtonDown();
	bool IsRightButtonDown();
	
	bool IsMouseWheelUp();
	bool IsMouseWheelDown();

	void PressLeftButton();
	void ReleaseLeftButton();
	void PressRightButton();
	void ReleaseRightButton();

	void MouseWheelUp();
	void MouseWheelNotUp();
	void MouseWheelDown();
	void MouseWheelNotDown();
};