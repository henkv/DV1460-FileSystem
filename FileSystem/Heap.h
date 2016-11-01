#pragma once
#include <utility>
#include <exception>
using namespace std;

template<typename T>
class Heap
{
private:
	T** elements;
	size_t nrOfElements;
	size_t elementCapacity;

	void percolateUp(size_t i)
	{
		if (i != 0)
		{
			size_t parent = (i - 1) / 2;

			if (*elements[i] < *elements[parent])
			{
				swap(elements[i], elements[parent]);
				percolateUp(i);
			}
		}
	}

	void percolateDown(size_t i)
	{
		size_t left = (i * 2) + 1, 
			   right = left + 1,
			   min = left;
		
		if (left < nrOfElements)
		{
			if (right < nrOfElements && *elements[right] < *elements[left])
			{
				min = right;
			}

			if (*elements[min] < *elements[i])
			{
				swap(elements[min], elements[i]);
				percolateUp(min);
			}
		}
	}

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
	Heap(size_t elementCapacity = 250)
	{
		this->elementCapacity = elementCapacity;
		this->elements = new T*[elementCapacity];
		this->nrOfElements = 0;
	}


	virtual ~Heap()
	{
		for (size_t i = 0; i < nrOfElements; i++)
		{
			delete elements[i];
		}
		delete[] elements;
	}


	void push(T const& element)
	{
		if (nrOfElements == elementCapacity)
			expand();

		elements[nrOfElements] = new T(element);
		percolateUp(nrOfElements++);
	}

	T pop()
	{
		if (nrOfElements == 0)
			throw exception("heap empty");

		T output = *elements[0];
		delete elements[0];
		elements[0] = nullptr;

		swap(elements[0], elements[--nrOfElements]);
		percolateDown(0);

		return output;
	}

	size_t size()
	{
		return nrOfElements;
	}

	void empty()
	{
		for (size_t i = 0; i < nrOfElements; i++)
		{
			delete elements[i];
			elements[i] = nullptr;
		}

		nrOfElements = 0;
	}

	Heap(Heap const& other) = delete;
	void operator=(Heap const& other) = delete;
};

