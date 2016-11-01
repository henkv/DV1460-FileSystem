#pragma once
#include "FSNode.h"
#include "Folder.h"

class File : public FSNode
{
private:
	string content;

public:
	File(int index, string name = "", Folder* parent = nullptr);
	virtual ~File();

	string getContent();
	void   setContent(string content);

	string toString();
};

