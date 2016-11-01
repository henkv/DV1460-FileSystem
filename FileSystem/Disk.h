#pragma once
#include "Block.h"
#include "FSNode.h"
#include "Folder.h"
#include "File.h"

class Disk
{
private:
	Block blocks[250];

public:
	Disk();
	~Disk();

	int getFreeBlock();

	bool writeBlock(size_t index, string data);
	bool writeBlock(FSNode* node);
	FSNode * readBlock(size_t index, Folder * parent = nullptr);
	void freeBlock(size_t index);

	void saveImage(string filename);
	bool loadImage(string filename);

	void format();
};

