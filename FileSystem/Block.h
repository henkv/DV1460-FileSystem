#pragma once
#include <string>
using namespace std;

class Block
{
private:
	char bytes[512];

public:
	Block();
	~Block();

	char& operator[](size_t index);

	void reset();
	bool write(string data);
	string read();
};

