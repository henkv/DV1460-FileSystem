#include "File.h"


File::File(int index, string name, Folder * parent) : FSNode(index, name, parent)
{
	content = "";
}

File::~File()
{
}

string File::getContent()
{
	return content;
}

void File::setContent(string content)
{
	this->content = content;
}



string File::toString()
{
	string output = "";
	
	output += (char)FSNode::FILE;
	output += getName();
	output += (char)0;
	output += content;

	return output;
}
