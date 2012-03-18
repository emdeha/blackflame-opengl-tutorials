#include <iostream>
using namespace std;

template<class type>
class Array
{
private:
	type *elements;
	int size;

public:
	Array();
	Array(type *newElements, int newSize);

	Array(const Array &copy);

	~Array();

	void Add(type element);

	type operator[](int index);
	Array operator=(const Array &other);
};

template<class type>
Array<type>::Array()
{
	size = 0;
	elements = new type[size];
}

template<class type>
Array<type>::Array(type *newElements, int newSize)
{
	size = newSize;
	elements = new type[size];
	for(int i = 0; i < size; i++)
	{
		elements[i] = newElements[i];
	}
}

template<class type>
Array<type>::Array(const Array &other)
{
	size = other.size;

	elements = new type[size];
	for(int i = 0; i < size; i++)
	{
		elements[i] = other.elements[i];
	}
}

template<class type>
Array<type>::~Array()
{
	if(elements != NULL)
	{
		delete[] elements;
	}
}

template<class type>
void Array<type>::Add(type element)
{
	type *oldElements = new type[size];
	for(int i = 0; i < size; i++)
	{
		oldElements[i] = elements[i];
	}

	size = size + 1;

	elements = new type[size];
	for(int i = 0; i < size; i++)
	{
		elements[i] = oldElements[i];
	}
	elements[size - 1] = element;
}

template<class type>
type Array<type>::operator[](int index)
{
	if(index > size - 1)
	{
		cout<<"Index out of bounds"<<endl;
		exit(0);
	}
	else
		return elements[index];
}

template<class type>
Array<type> Array<type>::operator=(const Array &other)
{
	if(this == &other)
	{
		return *this;
	}

	size = other.size;

	elements = new type[size];
	for(int i = 0; i < size; i++)
	{
		elements[i] = other.elements[i];
	}

	return *this;
}

int main()
{
	Array<int> myIntArray;
	for(int i = 0; i < 100; i++)
	{
		myIntArray.Add(i);
	}

	for(int i = 0; i < 100; i++)
	{
		cout<<i<<" element: ";
		cout<<myIntArray[i]<<endl;
	}

	int elems[5] = { 2, 3, 4, 5, 10 };
	myIntArray = Array<int>(elems, 5);

	for(int i = 0; i < 5; i++)
	{
		cout<<i<<" element: ";
		cout<<myIntArray[i]<<endl;
	}

	return 0;
}