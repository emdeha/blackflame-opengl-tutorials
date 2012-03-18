#include <iostream>
#include <vector>
using namespace std;

class Vehicle
{
protected:
	float position;

public:
	Vehicle()
	{
		position = 0.0f;
		//cout<<"Base constructor."<<endl;
	}
	Vehicle(float newPosition)
	{ 
		position = newPosition;
	}

	~Vehicle()
	{
		//cout<<"Base destructor."<<endl;
	}

	virtual void Move()
	{
		cout<<"Base moves"<<endl;
	}
};

class Car : public Vehicle
{
private:
	int passangers;

public:
	Car()
	{
		passangers = 0;
		//cout<<"Car constructor."<<endl;
	}
	Car(int newPassangers, float newPosition) : Vehicle(newPosition) 
	{
		passangers = newPassangers;
	}

	~Car()
	{
		//cout<<"Car destructor."<<endl;
	}

	void Move()
	{
		cout<<"Car moves"<<endl;
	}
};

class Truck : public Vehicle
{
private:
	int tonage;

public:
	Truck()
	{
		tonage = 0;
		//cout<<"Truck constructor."<<endl;
	}
	Truck(int newTonage, float newPosition) : Vehicle(newPosition)
	{
		tonage = newTonage;
	}

	void Move()
	{
		cout<<"Truck moves"<<endl;
	}
};

int main()
{
	std::vector<Vehicle*> vehicles;
	Car myCar(4, 5);
	Truck myTruck(3, 4);
	Vehicle myVehicle(3);

	vehicles.push_back(&myCar);
	vehicles.push_back(&myTruck);
	vehicles.push_back(&myVehicle);

	for(int i = 0; i < 3; i++)
	{
		vehicles[i]->Move();
	}
	//Car myCar;

	return 0;
}