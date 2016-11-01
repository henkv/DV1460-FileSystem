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

	for (int i = 1; i < 250 && output == -1; i++)
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

FSNode* Disk::readBlock(size_t index, Folder* parent)
{
	if (index > 249)
		throw out_of_range("index out of range");

	FSNode* output = nullptr;
	string block = blocks[index].read();
	size_t firstZero = block.find((char)0);
	size_t secondZero = block.find((char)0, firstZero + 1);
	string name = block.substr(1, firstZero - 1);
	string content = block.substr(firstZero + 1, secondZero - (firstZero + 1));

	if (block[0] == FSNode::FOLDER)
	{
		Folder* folder = new Folder(index, name, parent);

		for (size_t i = 0, size = content.size(); i < size; i++)
		{
			folder->addChild(readBlock(content[i], folder));
		}

		output = folder;
	}
	else if (blocks[index][0] == FSNode::FILE)
	{
		File* file = new File(index, name, parent);
		file->setContent(content);
		output = file;
	}

	return output;
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
