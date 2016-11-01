#pragma once
#include "FSNode.h"
#include "ArrayList.h"

class Folder : public FSNode
{
private:
	ArrayList<FSNode*> children;
public:
	Folder(int index, string name = "", Folder* parent = nullptr);
	virtual ~Folder();

	void addChild(FSNode* child);
	FSNode* getChild(string name);
	bool removeChild(FSNode* child);
	
	size_t size();
	FSNode* operator[](size_t index);

	string toString();
};

