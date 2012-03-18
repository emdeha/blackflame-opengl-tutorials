#include <iostream>
#include <vector>
using namespace std;

class MathUtil
{
public:
	static float SquareRoot(float x);
	static float Cos(float x);
	static float Sin(float x);
	static float Power(float x, int pow);
};

class ParticleEngine
{
private:
	float x, y, z;
	float r, g, b;

public:
	static void Update(ParticleEngine particles[]);
	static void Render(ParticleEngine particles[]);
};

void ParticleEngine::Update(ParticleEngine particles[])
{
	for(int i = 0; i < 100; i++)
	{
		particles[i].x += 1.3f;
	}
}

ParticleEngine particles[100];

void MainLoop()
{
	while(true)
	{
		ParticleEngine::Update(particles);
		ParticleEngine::Render(particles);
	}
}

int main()
{
	return 0;
}