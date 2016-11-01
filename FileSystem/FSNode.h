#pragma once
#include <string>
#include <exception>
using namespace std;

class FSNode
{
private:
	int	index;
	string name;
	FSNode* parent;

public:
	enum Type {EMPTY, FOLDER, FILE};

	FSNode(int index, string name = "", FSNode* parent = nullptr);
	virtual ~FSNode();

	int getIndex();
	string getName();
	FSNode* getParent();

	void setIndex(int index);
	void setName(string name);
	void setParent(FSNode* parent);	

	virtual string toString() = 0;
};

