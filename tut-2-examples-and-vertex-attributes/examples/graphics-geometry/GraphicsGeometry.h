#ifdef GRAPHICSGEOMETRY_EXPORTS
#define GRAPHICSGEOMETRY_API __declspec(dllexport)
#else
#define GRAPHICSGEOMETRY_API __declspec(dllimport)
#endif

class GRAPHICSGEOMETRY_API Vector3D
{
	float x;
	float y;
	float z;

public:
	Vector3D();
	Vector3D(float newX, float newY, float newZ);

	float GetLength();

	static void Normalize(Vector3D &A);
};