#include "Folder.h"






Folder::Folder(int index, string name, Folder * parent) : FSNode(index, name, parent)
{
}

Folder::~Folder()
{
}

void Folder::addChild(FSNode * child)
{
	children.push(child);
}

FSNode* Folder::getChild(string name)
{
	FSNode* output = nullptr;

	for (size_t i = 0, size = children.size(); i < size && output == nullptr; i++)
	{
		if (name == children[i]->getName())
		{
			output = children[i];
		}
	}

	return output;
}

bool Folder::removeChild(FSNode * child)
{
	bool output = false;
	FSNode* trash = nullptr;

	for (size_t i = 0, size = children.size(); i < size && output == false; i++)
	{
		if (child == children[i])
		{
			children.remove(i);
			output = true;
		}
	}

	return output;
}

size_t Folder::size()
{
	return children.size();
}

FSNode * Folder::operator[](size_t index)
{
	return children[index];
}

string Folder::toString()
{
	string output = "";

	output += (char)FSNode::FOLDER;
	output += getName();
	output += (char)0;

	for (size_t i = 0, size = children.size(); i < size; i++)
	{
		output += (char)children[i]->getIndex();
	}

	output += (char)0;

	return output;
}
