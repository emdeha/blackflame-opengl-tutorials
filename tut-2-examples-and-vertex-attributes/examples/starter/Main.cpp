#include <iostream>
using namespace std;

/*** Cohesion ***/
// Strong cohesion
class MathFunctions
{
public:
	static void Square(double x);
	static void Absolute(double x);
	static void Sin(double x_angle);
	static void Cos(double x_angle);
};

// Weak cohesion
// The easy-to-see example
class Magic
{
public:
	void PrintDoc();
	void CreateReport(string data);
	void ReleaseConnection();

	bool IsTomHere();

	void FindSocket();
};
// The little harder-to-see example
class Document
{
private:
	string text;
	int format;

public:
	Document();

	void ConstructDocument();
	void ConvertToA4();
	void ConvertToA3();

	void Print(); // Gotcha!
};

/*** Coupling ***/
// Loose coupling
class Report
{
private:
	string text;
	int format;

public:
	Report();

	bool LoadFromFile(string path);
	bool SaveToFile(string path);
};
class Printer
{
public:
	static bool Print(Report report);
};
int LooseCouplingMain()
{
	Report myReport;
	myReport.LoadFromFile("../Reports/weekly.rep");
	Printer::Print(myReport);
}

// Thight coupling
class Rocket
{
private:
	float velocity;
	int explosionType;

public:
	Rocket();

	void SetVelocity(float newVelocity);
	void SetExplosionType(int newExplosionType);
};
class RocketLauncher
{
public:
	static void LaunchRocket(Rocket myRocket);
};
int TightCouplingMain()
{
	Rocket destroyerTwelve;
	destroyerTwelve.SetVelocity(12.4);
	destroyerTwelve.SetExplosionType(4);

	RocketLauncher::LaunchRocket(destroyerTwelve);
}

/*** Some spaghetti ***/
class Planet;

class Doroty
{
private:
	bool isPlanetDestroyed;
	float position;

public:
	Doroty();

	void Update();
	void Render();

	void Suicide()
	{
		this->position = -1;
	}
};

class Zoro
{
private:
	float position;

public:
	Zoro();

	void Update();
	void Render();

	void KillDoroty(Doroty &doroty)
	{
		doroty.Suicide();
	}

	static void RemoveChild(const Planet &parentPlanet);
};

class Planet
{
private:
	float velocity;
	Planet *parent;
	bool isFlat;

public:
	Planet();

	void Update();
	void Render();

	void KillDoroty(Zoro &zoro, Doroty &doroty)
	{
		zoro.KillDoroty(doroty);
	}
	bool IsZoroKilled(Zoro myZoro);
};


int main()
{
	return 0;
} 