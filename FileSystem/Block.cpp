#include "Block.h"
#include <exception>

Block::Block()
{
	reset();
}

Block::~Block()
{
}

char & Block::operator[](size_t index)
{
	if (index > 511) 
		throw out_of_range("index out of range");

	return bytes[index];
}

void Block::reset()
{
	for (int i = 0; i < 512; i++)
	{
		bytes[i] = '\0';
	}
}

bool Block::write(string data)
{
	bool output = false;
	size_t size = data.size();

	if (size < 512)
	{
		for (int i = 0; i < size; i++)
		{
			bytes[i] = data[i];
		}

		for (int i = size; i < 512; i++)
		{
			bytes[i] = '\0';
		}

		output = true;
	}

	return output;
}

string Block::read()
{
	string output = "";

	for (size_t i = 0; i < 512; i++)
	{
		output += bytes[i];
	}

	return output;
}
