#include <iostream>
using namespace std;

class Object
{
protected: 
	float position;

public:
	Object();
	Object(float newPosition) : position(newPosition) { }

	virtual void Move(float delta) = 0;
};

class Human : public Object
{
public:
	void Move(float delta)
	{
		position += delta;
	}
};

class Raptor : public Object
{
public:
	void Move(float delta)
	{
		position += 2 * delta;
	}
};

int main()
{
	Raptor phylosoraptor(3.4f);

	return 0;
}