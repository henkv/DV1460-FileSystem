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

	//createImage <filnamn> sparar det simulerade systemet på en fil på datorns hårddisk så att den går att återskapa vid ett senare tillfälle.
	void createImage(string filename);
	
	//restoreImage <filnamn> återstället systemet från en fil på datorns hårddisk.
	bool restoreImage(string filename);
	
	//ls listar innehållet i aktuellt katalog(filer och undermappar).
	string ls(string path);

	//create <filnamn> skapar en fil på den simulerande disken(datainnehållet skrivs in på en extra tom rad)
	bool create(string path, string content);

	//cat <filnamn> skriver ut innehållet i filen filnamn på skärmen.
	string cat(string path);

	//copy <fil1> <fil2> skapar en ny fil fil2 som är en kopia av den existerande fil fil1.
	bool copy(string path1, string path2);

	//mkdir <katalognamn> skapar en ny tom katalog på den simulerande disken.
	bool mkdir(string path);

	//cd <katalognamn> ändrar aktuell katalog till den angivna katalogen på den simulerade disken.
	bool cd(string path);

	//pwd skriver ut den fullständiga sökvägen ändå från roten till filnamnet.
	string pwd();

	//rm <filnamn> tar bort angiven fil från den simulerade disken.
	bool rm(string path);
};

