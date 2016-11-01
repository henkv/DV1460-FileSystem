#include "FSNode.h"


FSNode::FSNode(int index, string name, FSNode* parent)
{
	this->parent = parent;
	this->index = index;
	this->setName(name);
}

FSNode::~FSNode()
{
}

int FSNode::getIndex()
{
	return index;
}

string FSNode::getName()
{
	return name;
}

FSNode * FSNode::getParent()
{
	return parent;
}

void FSNode::setIndex(int index)
{
	this->index = index;
}

void FSNode::setName(string name)
{
	if (name.size() > 100)
		throw length_error("name too long");

	this->name = name;
}

void FSNode::setParent(FSNode* parent)
{
	this->parent = parent;
}
