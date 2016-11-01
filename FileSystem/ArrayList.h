#pragma once
#include <utility>
#include <exception>
using namespace std;

template<typename T>
class ArrayList
{
private:
	T** elements;
	size_t nrOfElements;
	size_t elementCapacity;

	void expand()
	{
		elementCapacity += 10;
		T** newElements = new T*[elementCapacity];

		for (int i = 0; i < nrOfElements; i++)
		{
			newElements[i] = elements[i];
		}

		delete[] elements;
		elements = newElements;
	}

public:
	ArrayList(size_t elementCapacity = 250)
	{
		this->elementCapacity = elementCapacity;
		this->elements = new T*[elementCapacity];
		this->nrOfElements = 0;
	}


	virtual ~ArrayList()
	{
		for (size_t i = 0; i < nrOfElements; i++)
		{
			delete elements[i];
		}
		delete[] elements;
	}

	T& operator[](size_t index)
	{
		if (index >= nrOfElements)
			throw exception("index out of range");

		return *elements[index];
	}

	void push(T const& element)
	{
		if (nrOfElements == elementCapacity)
			expand();

		elements[nrOfElements++] = new T(element);
	}

	T remove(size_t index)
	{
		if (index >= nrOfElements)
			throw exception("index out of range");

		T output = *elements[index];

		delete elements[index];
		elements[index] = nullptr;
		swap(elements[index], elements[--nrOfElements]);

		return output;
	}
	
	size_t size()
	{
		return nrOfElements;
	}

	ArrayList(ArrayList const& other) = delete;
	void operator=(ArrayList const& other) = delete;
};

