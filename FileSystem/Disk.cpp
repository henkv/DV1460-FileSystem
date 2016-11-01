#include "Disk.h"

#include <fstream>


Disk::Disk()
{
	
}


Disk::~Disk()
{
}

int Disk::getFreeBlock()
{
	int output = -1;

	for (int i = 1; i < 250 && output != -1; i++)
	{
		if (blocks[i][0] == 0)
		{
			output = i;
		}
	}

	return output;
}

bool Disk::writeBlock(size_t index, string data)
{
	if (index > 249)
		throw out_of_range("index out of range");

	return blocks[index].write(data);
}

bool Disk::writeBlock(FSNode * node)
{
	return blocks[node->getIndex()].write(node->toString());
}

FSNode* Disk::readBlock(size_t index)
{
	if (index > 249)
		throw out_of_range("index out of range");

	return nullptr;
}

void Disk::freeBlock(size_t index)
{
	blocks[index].reset();
}

void Disk::saveImage(string filename)
{
	ofstream file(filename, ios::binary);
	file.write((char*)blocks, sizeof(blocks));
	file.close();
}

bool Disk::loadImage(string filename)
{
	bool output = false;
	ifstream file(filename, ios::binary);

	if (file) {
		file.read((char*)blocks, sizeof(blocks));
		output = true;
	}

	file.close();
	return output;
}

void Disk::format()
{
	for (int i = 0; i < 250; i++)
	{
		blocks[i].reset();
	}
}
