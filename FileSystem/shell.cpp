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

//quit lämnar körningen <Redan gjord i filsystemet>
//format bygger upp ett tomt filsystem, dvs.formatterar disken.
//createImage <filnamn> sparar det simulerade systemet på en fil på datorns hårddisk så att den går att återskapa vid ett senare tillfälle.
//restoreImage <filnamn> återstället systemet från en fil på datorns hårddisk.

//create <filnamn> skapar en fil på den simulerande disken(datainnehållet skrivs in på en extra tom rad)
//cat <filnamn> skriver ut innehållet i filen filnamn på skärmen.
//ls listar innehållet i aktuellt katalog(filer och undermappar).
//copy <fil1> <fil2> skapar en ny fil fil2 som är en kopia av den existerande fil fil1.
//mkdir <katalognamn> skapar en ny tom katalog på den simulerande disken.
//cd <katalognamn> ändrar aktuell katalog till den angivna katalogen på den simulerade disken.
//pwd skriver ut den fullständiga sökvägen ändå från roten till filnamnet.
//rm <filnamn> tar bort angiven fil från den simulerade disken.