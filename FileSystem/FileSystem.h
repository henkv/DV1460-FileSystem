#pragma once
#include <string>
using namespace std;

#include "Disk.h"
#include "Folder.h"
#include "File.h"

class FileSystem
{
private:
	Disk disk;
	Folder* root;
	Folder* currentDir;

	void deleteNode(FSNode* node);
	FSNode* resolvePath(string path);
	void splitPath(string& path, string& name);
public:
	FileSystem();
	~FileSystem();

	//format bygger upp ett tomt filsystem, dvs.formatterar disken.
	void format();

	//createImage <filnamn> sparar det simulerade systemet p� en fil p� datorns h�rddisk s� att den g�r att �terskapa vid ett senare tillf�lle.
	void createImage(string filename);
	
	//restoreImage <filnamn> �terst�llet systemet fr�n en fil p� datorns h�rddisk.
	bool restoreImage(string filename);
	
	//ls listar inneh�llet i aktuellt katalog(filer och undermappar).
	string ls(string path);

	//create <filnamn> skapar en fil p� den simulerande disken(datainneh�llet skrivs in p� en extra tom rad)
	bool create(string path, string content);

	//cat <filnamn> skriver ut inneh�llet i filen filnamn p� sk�rmen.
	string cat(string path);

	//copy <fil1> <fil2> skapar en ny fil fil2 som �r en kopia av den existerande fil fil1.
	bool copy(string path1, string path2);

	//mkdir <katalognamn> skapar en ny tom katalog p� den simulerande disken.
	bool mkdir(string path);

	//cd <katalognamn> �ndrar aktuell katalog till den angivna katalogen p� den simulerade disken.
	bool cd(string path);

	//pwd skriver ut den fullst�ndiga s�kv�gen �nd� fr�n roten till filnamnet.
	string pwd();

	//rm <filnamn> tar bort angiven fil fr�n den simulerade disken.
	bool rm(string path);
};

