#include "FileSystem.h"
#include <sstream>


void FileSystem::deleteNode(FSNode * node)
{
	Folder* dir = dynamic_cast<Folder*>(node);

	if (dir != nullptr)
	{
		while (dir->size() > 0)
		{
			deleteNode((*dir)[0]);
		}
	}

	((Folder*)node->getParent())->removeChild(node);
	disk.freeBlock(node->getIndex());
	delete node;
}

FSNode* FileSystem::resolvePath(string path)
{
	istringstream sstream;
	string field;
	FSNode* output;
	Folder* parent;

	if (path.find('/') == 0)
	{
		output = root;
		sstream.str(path.substr(1));
	}
	else
	{
		output = currentDir;
		sstream.str(path);
	}

	while (getline(sstream, field, '/') && output != nullptr)
	{
		if (field == ".");
		else if (field == "..")
		{
			output = output->getParent();
		}
		else
		{
			parent = dynamic_cast<Folder*>(output);
			if (parent != nullptr)
			{
				output = parent->getChild(field);
			}
		}
	}

	return output;
}

void FileSystem::splitPath(string & path, string & name)
{
	string originalPath = path;
	size_t lastSlash = originalPath.find_last_of('/');

	if (lastSlash < originalPath.size() - 1)
	{
		path = originalPath.substr(0, lastSlash);
		name = originalPath.substr(lastSlash + 1);
	}
	else
	{
		path = ".";
		name = originalPath.substr(0, lastSlash);
	}
}

FileSystem::FileSystem()
{
	root = new Folder(0);
	root->setParent(root);
	currentDir = root;
	disk.writeBlock(root);
}

FileSystem::~FileSystem()
{
	deleteNode(root);
}

void FileSystem::format()
{
	deleteNode(root);
	root = new Folder(0);
	root->setParent(root);
	currentDir = root;
	disk.writeBlock(root);
}

void FileSystem::createImage(string filename)
{
	disk.saveImage(filename);
}

bool FileSystem::restoreImage(string filename)
{
	Disk temp;
	bool output = temp.loadImage(filename);
	
	if (output)
	{
		deleteNode(root);
		disk = temp;
		root = (Folder*)disk.readBlock(0);
		root->setParent(root);
		currentDir = root;
	}

	return output;
}

string FileSystem::ls(string path)
{
	string output = "Cant resolve path";
	Folder* dir = dynamic_cast<Folder*>(resolvePath(path));
	FSNode* child;
	string type;

	if (dir != nullptr)
	{
		output = "### > folder ### - file ###\n";
		for (size_t i = 0, size = dir->size(); i < size; i++)
		{
			child = (*dir)[i];
			type = dynamic_cast<Folder*>(child) != nullptr ? "> " : "- ";
			output += type + child->getName() + "\n";
		}
	}

	return output;
}

bool FileSystem::create(string path, string content)
{
	bool output = false;
	
	string name;
	splitPath(path, name);

	Folder* parent = dynamic_cast<Folder*>(resolvePath(path));

	if (parent != nullptr)
	{
		if (parent->getChild(name) == nullptr)
		{
			int index = disk.getFreeBlock();
			if (index != -1)
			{
				File* file = new File(index, name, parent);
				file->setContent(content);
				parent->addChild(file);

				disk.writeBlock(file);
				disk.writeBlock(parent);

				output = true;
			}
		}
	}

	return output;
}

string FileSystem::cat(string path)
{
	string output = "Could not find file.";
	
	File* file = dynamic_cast<File*>(resolvePath(path));

	if (file != nullptr)
	{
		output = file->getContent();
	}

	return output;
}

bool FileSystem::copy(string path1, string path2)
{
	bool output = false;

	File* original = dynamic_cast<File*>(resolvePath(path1));

	if (original != nullptr)
	{
		output = create(path2, original->getContent());
	}

	return output;
}

bool FileSystem::mkdir(string path)
{
	bool output = false;

	string name;
	splitPath(path, name);

	Folder* parent = dynamic_cast<Folder*>(resolvePath(path));

	if (parent != nullptr)
	{
		if (parent->getChild(name) == nullptr)
		{
			int index = disk.getFreeBlock();
			if (index != -1)
			{
				Folder* folder = new Folder(index, name, parent);
				parent->addChild(folder);

				disk.writeBlock(folder);
				disk.writeBlock(parent);

				output = true;
			}
		}
	}

	return output;
}

bool FileSystem::cd(string path)
{
	bool output = false;

	Folder* dir = dynamic_cast<Folder*>(resolvePath(path));
	if (dir != nullptr)
	{
		currentDir = dir;
		output = true;
	}

	return output;
}

string FileSystem::pwd()
{
	string output = "";

	FSNode* walker = currentDir;
	while (walker != root)
	{
		output = "/" + walker->getName() + output;
		walker = walker->getParent();
	}
	
	if (output.size() == 0)
		output = "/";

	return output;
}

bool FileSystem::rm(string path)
{
	bool output = false;

	FSNode* trash = resolvePath(path);
	if (trash != nullptr && trash != root)
	{
		deleteNode(trash);
		output = true;
	}

	return output;
}
