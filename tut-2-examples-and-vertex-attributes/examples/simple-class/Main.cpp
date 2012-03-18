#include <iostream>
#include <string.h>
using namespace std;

// Class declaration
// TODO: Also introduce destructors
class SimpleClass
{
private:
	int fieldInt;
	char fieldChar;

	float *ptrFloat;

public:
	SimpleClass();
	SimpleClass(int newFieldInt, char newFieldChar, float &newPtrFloat);

	SimpleClass(const SimpleClass &object);

	~SimpleClass();

	SimpleClass operator=(const SimpleClass &other);

	void PrintContent();

	int GetInt();
	char GetChar();

	void SetChar(char ch);

	friend float* GetAdress(const SimpleClass &object);
};

// Class definition

SimpleClass::SimpleClass()
{
	fieldInt = 0;
	fieldChar = '\0';
	ptrFloat = new float;
}
SimpleClass::SimpleClass(int newFieldInt, char newFieldChar, float &newPtrFloat)
{
	fieldInt = newFieldInt;
	fieldChar = newFieldChar;

	ptrFloat = new float(newPtrFloat);
	*ptrFloat = newPtrFloat;
}

SimpleClass::SimpleClass(const SimpleClass &object)
{
	fieldInt = object.fieldInt;
	fieldChar = object.fieldChar;

	ptrFloat = new float(*object.ptrFloat);
	*ptrFloat = *object.ptrFloat;
}

SimpleClass SimpleClass::operator=(const SimpleClass &other)
{
	if(this == &other)
	{
		return *this;
	}

	fieldInt = other.fieldInt;
	fieldChar = other.fieldChar;

	ptrFloat = new float(*other.ptrFloat);
	*ptrFloat = *other.ptrFloat;

	return *this;
}

SimpleClass::~SimpleClass()
{
	if(ptrFloat != NULL)
	{
		delete ptrFloat;
	}
}

void SimpleClass::PrintContent()
{
	cout<<"Int: "<<fieldInt<<endl;
	cout<<"Char: "<<fieldChar<<endl;
	cout<<"Float: "<<*ptrFloat<<" Adress: "<<ptrFloat<<endl;
}

int SimpleClass::GetInt()
{
	return fieldInt;
}
char SimpleClass::GetChar()
{
	return fieldChar;
}

void SimpleClass::SetChar(char ch)
{
	fieldChar = ch;
}

float* GetAdress(const SimpleClass &object)
{
	return object.ptrFloat;
}

int main()
{
	SimpleClass myClass;
	myClass.PrintContent();
	
	float a = 5.5f;

	cout<<"My class: "<<endl;
	myClass = SimpleClass(5, 's', a);
	myClass.PrintContent();

	cout<<"Field int: "<<myClass.GetInt()<<endl;

	myClass.SetChar('f');
	cout<<endl<<"New field char: "<<myClass.GetChar()<<endl;

	cout<<endl<<"Adress of float: "<<GetAdress(myClass)<<endl;

	return 0;
}