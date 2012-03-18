#include <iostream>
#include <vector>
using namespace std;

class Vector2D
{
private:
	float x;
	float y;

public:
	Vector2D();
	Vector2D(float newX, float newY) : x(newX), y(newY) { }

	Vector2D operator+(const Vector2D &other);
	Vector2D operator+=(const Vector2D &other);
	bool operator==(const Vector2D &other);

	Vector2D operator-();

	Vector2D operator++(); // prefix
	Vector2D operator++(int); // postfix
};

Vector2D Vector2D::operator+(const Vector2D &other)
{
	return Vector2D(this->x + other.x, 
					this->y + other.y);
}

Vector2D Vector2D::operator+=(const Vector2D &other)
{
	this->x += other.x;
	this->y += other.y;

	return *this;
}

bool Vector2D::operator==(const Vector2D &other)
{
	if((this->x == other.x) &&
	   (this->y == other.y))
	{
		return true;
	}
	else
	{
		return false;
	}
}

Vector2D Vector2D::operator-()
{
	x = -x;
	y = -y;
	return *this;
}

Vector2D Vector2D::operator++()
{
	x++;
	y++;
	return *this;
}
Vector2D Vector2D::operator++(int)
{
	++x;
	++y;
	return *this;
}

int main()
{
	return 0;
}