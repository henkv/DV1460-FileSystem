#include <iostream>
#include <string>
#include <sstream>
#include "FileSystem.h"

using namespace std;


int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	int availableCommands = 12;
	string commands[] = {
		"quit", "format", "createImage", "createImage", "create",
		"cat", "ls", "copy", "mkdir", "cd", "pwd", "rm"
	};

	

	getline(cin, string());
	return 0;
}

//quit l�mnar k�rningen <Redan gjord i filsystemet>
//format bygger upp ett tomt filsystem, dvs.formatterar disken.
//createImage <filnamn> sparar det simulerade systemet p� en fil p� datorns h�rddisk s� att den g�r att �terskapa vid ett senare tillf�lle.
//restoreImage <filnamn> �terst�llet systemet fr�n en fil p� datorns h�rddisk.

//create <filnamn> skapar en fil p� den simulerande disken(datainneh�llet skrivs in p� en extra tom rad)
//cat <filnamn> skriver ut inneh�llet i filen filnamn p� sk�rmen.
//ls listar inneh�llet i aktuellt katalog(filer och undermappar).
//copy <fil1> <fil2> skapar en ny fil fil2 som �r en kopia av den existerande fil fil1.
//mkdir <katalognamn> skapar en ny tom katalog p� den simulerande disken.
//cd <katalognamn> �ndrar aktuell katalog till den angivna katalogen p� den simulerade disken.
//pwd skriver ut den fullst�ndiga s�kv�gen �nd� fr�n roten till filnamnet.
//rm <filnamn> tar bort angiven fil fr�n den simulerade disken.